#pragma once
#define barsInMelMeasure 4
#define FLT_MIN_PLUS          1.175494351e-38         /* min positive value */

#include "../JuceLibraryCode/JuceHeader.h"
#include "DspFaust.h"
#include "MusicInfoRead.h"
#include "MidiTrack_Drum.h"
#include "MusicPhaseCalc.h"
#include "ScaleTonicTrans.h"
#include "mixerSettings.h"
#include "FaustStrings.h"
#include "musicPerfRules.h"
#include "tempoTickIncCalculation.h"
#include "accentCalculation.h"

class Sequencer
{
public:
	Sequencer();
	~Sequencer();
	MusicPhaseCalc musicPhase;
	ScaleTonicTrans scaleTonicTrans;
	MusicInfoRead currentMusic;
	MidiTrack_Drum* percObj;
	Random randGen;
	DspFaust dspFaust;
	MixerSettings mixerSettings;
	FaustStrings faustStrings;
	TempoTickInc tempoTickInc;
	MusicPerfRules musicPerfRules;
	AccentCalculation accentCalculation;
	
	void resetCounters();
	short musicMode = 1;
	bool isFileLoaded = false;
	short index_baseBeat = 0;
	
	// FETCH RANDOM INDEX IN INTEGER RANGE SPECIFIED
	int fetchNewRandomIndex(int range)
	{
		return randGen.nextInt(range - 1);
	}

	// LOAD NEW MIDI SONG FILE
	void loadNewFile_MIDI(String name)
	{
		currentMusic.loadMidiFile(name);
		tempoTickInc.flushIncVector();
		tempoTickInc.generateTempoCurve(&currentMusic.midiTracks[0], &musicPerfRules);
		if (!isFileLoaded)
			isFileLoaded = true;
	}

	// BEAT AND BAR COUNTERS
	int pulsesElapsed = -1;	
	int beatsElapsed = -1; 	
	int barsElapsed = -1;
	int beatsElapsed_withinBar = 0;

	// SET RHYTHM TIMING MODE DEPENDING ON SONG NAME
	void setTimingMode(String path)
	{
		if (path.contains("3by4"))
		{
			timingMode = 2;
			isTripletMode = false;
			is3by4Mode = true;
		}
		else if (path.contains("Triplet"))
		{
			timingMode = 1;
			isTripletMode = true;
			is3by4Mode = false;
		}
		else
		{
			timingMode = 0;
			isTripletMode = false;
			is3by4Mode = false;
		}
		// SET SELECTED RHYTHM TO FIRST CHOICE WITH APPROPRIATE TIMING MODE
		for (int i = 0; i < currentMusic.styles[currentMusic.style_current].grooves_total; i++)
		{
			if (currentMusic.styles[currentMusic.style_current].groove_types[i] == timingMode)
			{
				index_baseBeat = i;
				break;
			}
		}
	}

	// TIMING MODE
	int ticksPerMeasure = 15360;
	short beatsInBar_TimingMode[10] = { 4, 4, 3 };
	short timingMode = 0;
	bool is3by4Mode = false;
	bool isTripletMode = false;
	float tapTempoCounter = 0;									
	bool isPlaying = false;										
	float timeElapsed_Song = 0;									
	float timeLeft_Song = 0;									
	float timeTotal_Song = 0;
	float tempo = 120;
	float timeElapsed_SONG = 0.0;								// PLAYBACK Time Elapsed
	int sixteenthNotesPerMeasure = 16;
	
	double lastPulseTime = 0.0;									// Last 16th Pulse Time
	double nextPulseTime = 0.0;									// Next 16th Pulse Time
	double ticksPerMS = 2.0;									// MIDI Ticks per ms
	long double midiTicksElapsed = 0.0;								// #MIDI Ticks elapsed
	int midiTickIncrement = 240;								// MIDI Tick Increment per 16th note
	double songProgress = 0;									// Song Process Fraction -> Sequencer

	// SEQUENCER SONIFICATION
	float AP_Val = 0;
	float AP_Val_2D_X = 0;
	float AP_Val_2D_Y = 0;
	String soni_AP_Name = "";

	//MIDI
	short numTracks = 8;
	float vels[4][8] = { 0.0 };
	bool note_isOn[4][8] = { false };
	bool isPitched[8] = 
	{ 
		false,												// KICK
		false,												// SNARE
		false,												// HH
		true,												// CHORD MAIN
		true,												// BASSLINE
		true,												// MAIN MELODY
		true,												// CHORD HIGH
		false												// CRASH
	};
	int pitches[4][8] = { 0 };
	float scaleDegree_Voices[4][8] =
	{
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1}
	};
	float accent_Voices[4][8] = 
	{
		{5,5,5,5,5,5,5,5},
		{5,5,5,5,5,5,5,5},
		{5,5,5,5,5,5,5,5},
		{5,5,5,5,5,5,5,5}
	};
	bool isVel_FromSongFile[8] =
	{
		false,
		false,
		false,
		false,
		false,
		true,
		false,
		false
	};
	short trackIdx_to_midiTrack_map[8] = { -1, -1, -1, 1, 2, 0, 1, -1 };

	bool isNewEvents_ToHandle[8] = {false};
	bool isNewEvents_PitchOnly[8] = { false };
	void check_Handle_New_MIDIEvents(double tickInc)
	{
		for (int i = 1; i <= numTracks; i++)
			checkNew_MIDIEvents_SINGLE(i,tickInc);
		mapNew_MIDIEvents();
	}
	void checkNew_MIDIEvents_SINGLE(int trackIndex, double tickInc);
	void mapNew_MIDIEvents();
	bool infoMapped_CurrentPulse_MIDI = false;

	// INCREMENT BAR AND BEAT COUNTERS
	void incrementPulseCounter();
	
	// RESET MIDI PLAYBACK (EVENT COUNTERS TO ZERO)
	void resetMidiPlayback()
	{
		for (int i = 0; i < 4; i++)
		{
			nextVoiceIndex[i] = 0;
			currentMusic.midiTracks[i].resetPlayback();
		}
	};
	
	// MIDI EVENT HANDLING
	short nextVoiceIndex[8] = { 0 };
	double nextEventTimeStamp[8] = { 0 };

	// UPDATE CHOSEN RHYTHM WITH NEXT
	void nextRhythm(short musicMode) 
	{
		currentMusic.styles[currentMusic.style_current].grooves[currentMusic.styles[currentMusic.style_current].groove_current].flush_nextEventIndices();
		currentMusic.styles[currentMusic.style_current].groove_current =
			(currentMusic.styles[currentMusic.style_current].groove_current + 1) % currentMusic.styles[currentMusic.style_current].grooves_total;
	};

	// SCALE AND TONIC TRANSFORMATIONS
	short scaleID_ORIG = 0;
	short scaleID_TRANS = 0;
	short tonicOffset_ORIG = 0;
	short tonicOffset_TRANS = 0;
	String cue_AP_Name = "";
	String X_2D_AP_Name = "";
	String Y_2D_AP_Name = "";

	// OCTAVE LIMIT MIDI NOTE WITHIN TWO BOUNDS
	int midiNoteLimit(short prelimValue, short lowerlim_MIDI, short upperlim_MIDI)
	{
		bool tooLow = lowerlim_MIDI > prelimValue; short tooLow_num = tooLow ? 1 : 0;
		bool tooHigh = upperlim_MIDI < prelimValue; short tooHigh_num = tooHigh ? 1 : 0;
		short octavesUnder = ((lowerlim_MIDI - prelimValue)*tooLow_num / 12) + tooLow_num;
		short octavesOver = ((prelimValue - upperlim_MIDI)*tooHigh_num / 12) + tooHigh_num;
		return prelimValue + 12 * octavesUnder - 12 * octavesOver;
	};

	// RESET PERC MIDI OBJECTS WHEN RHYTHM CHANGED - ADAPTS NEXT EVENT INDICES
	void resetPercMIDIOnChange(double midiTicksElapsed)
	{
		// FIND MOD MIDI TICKS ELAPSED
		double midiTicksElapsed_MOD = midiTicksElapsed - (int)((int)midiTicksElapsed / 15360) * 15360;
		
		// RESET NEXT EVENT INDICES TO ZERO
		currentMusic.styles[currentMusic.style_current].grooves[currentMusic.styles[currentMusic.style_current].groove_current].flush_nextEventIndices();
		int eventIdx_Present_Trackwise = 0;

		for (int h = 0; h < numTracks; h++)
		{	// i REPRESENTS IDX OF TRACKWISE EVENTS
			for (int i = 0; i < currentMusic.styles[currentMusic.style_current].grooves[currentMusic.styles[currentMusic.style_current].groove_current].eventCount_ByTrack[h]; i++)
			{
				eventIdx_Present_Trackwise = currentMusic.styles[currentMusic.style_current].grooves[currentMusic.styles[currentMusic.style_current].groove_current].eventIdx_ByTrack_ALL[i][h];
				if (midiTicksElapsed_MOD < currentMusic.styles[currentMusic.style_current].grooves[currentMusic.styles[currentMusic.style_current].groove_current].infoMatrix[eventIdx_Present_Trackwise][3])
				{
					currentMusic.styles[currentMusic.style_current].grooves[currentMusic.styles[currentMusic.style_current].groove_current].eventIdx_ByTrack_NEXT[h] = i;
					break;
				}
			}
		}
	};

	// COOK LOADED MIDI VELOCITY TO DSPFAUST COMPATIBLE
	float cookMIDIVel(float midiVel, short trackIndex, String APName)
	{
		float output = 0;

		if (midiVel < 32)
			output = pow(midiVel / 32.0, 2);
		else
			output = 1 + 9.0 / 95.0 * (midiVel - 32);

		return output;
	};

	//Toggle Mute Status
	short muteValues[8] = { 0 };

	// ARRANGE PITCHES ASCENDING
	void arrangePitches_Asc(int trackIndex)
	{	
		int temp[4] = { 0 };
		for (int i = 0; i < 4; i++)
			temp[i] = pitches[i][trackIndex];
		std::sort(temp, temp + currentMusic.numVoices[trackIndex]);
		for (int i = 0; i < 4; i++)
			pitches[i][trackIndex] = temp[i];
	}

	void copyPitches_ToDependentTracks(int trackIndex)
	{
		int targetTrackId = trackIdx_to_midiTrack_map[trackIndex];
		int trackVariant = 0;

		for (int i = 0; i < numTracks; i++)
		{
			trackVariant = currentMusic.styles[currentMusic.style_current].variantConfig[i] - 1;
			if (i != trackIndex && trackIdx_to_midiTrack_map[i] == targetTrackId)
			{
				for (int j = 0; j < currentMusic.numVoices[trackIndex]; j++)
					pitches[j][i] = midiNoteLimit(pitches[j][trackIndex],
						mixerSettings.var_noteMins[trackVariant][j][i],
						mixerSettings.var_noteMaxs[trackVariant][j][i]);
			}
		}
	}

	// DSPFAUST RELATED
	//Start DSPFaust, Initialize Gain -> Sequencer
	void onStartMusic()
	{
		dspFaust.start();
		initializeTracksForPlayback();
	}
	void initializeTracksForPlayback();
	void applyCurrentVariantGain(int trackIndex);
	void setTrackGains(int trackIndex, float value);
	void setTrackMutes(int trackIndex, int value);
	void applyCurrentVariantEQ(int trackIndex);
	void applyCurrentVariantComp(int trackIndex);
	//Set Master Gain -> Sequencer		
	void applyMasterGain(float value)
	{
		mixerSettings.masterGain = value;
		std::string address = faustStrings.baseName + faustStrings.MasterVol;
		dspFaust.setParamValue(address.c_str(), value);
	}
	void switchInstVariant(int trackIndex, int newVariant);
	void setFilename(String name);
	bool handleTapTempoPress();
	void togglePlayPause();
	void stopMusic();
	// Song Completion Fraction -> Sequencer
	bool getSongProgress()
	{
		songProgress = midiTicksElapsed / currentMusic.finalTimeStamp;
		timeLeft_Song = (currentMusic.finalTimeStamp - midiTicksElapsed) / (1000 * ticksPerMS);
		if (songProgress >= 1)
			return true;
		else return false;
	}

	// UPDATE INBUILT MELODY IN CURRENTMUSIC
	void flushInbuiltMelody()
	{
		for (int i = 0; i < currentMusic.midiTracks[0].numEvents; i++)
		{
			currentMusic.midiTracks[0].infoMatrix[i][1] = scaleTonicTrans.inbuilt_BaseKey;
		}
	}

	void updateInbuiltMelody(int row, int col, int vel) // 0 -7 // 0 - 15
	{
		currentMusic.presentDegrees[col] = row + 1;
		int midiKeyToWrite = scaleTonicTrans.getMidiKeyFromDegree
		(currentMusic.presentDegrees[col], scaleID_TRANS, tonicOffset_TRANS);
		int sixteenthTicks = 240;
		int noteLength = 60;

		for (int i = 0; i < currentMusic.midiTracks[0].numEvents; i++)
		{
			if (((currentMusic.midiTracks[0].infoMatrix[i][3] / 240) % 16) == col)
			{
				if (currentMusic.midiTracks[0].infoMatrix[i][0] == 1 || currentMusic.midiTracks[0].infoMatrix[i][0] == 5)
				{
					currentMusic.midiTracks[0].infoMatrix[i][1] = midiKeyToWrite;
					currentMusic.midiTracks[0].infoMatrix[i][0] = vel > 73 ? 1 : 5;
					currentMusic.midiTracks[0].infoMatrix[i][2] = vel;
					currentMusic.midiTracks[0].infoMatrix[i + 1][1] = midiKeyToWrite;
				}
			}
		}
	}

	void setTimeSignatureInbuilt(int numSixteenthNotes)
	{
		sixteenthNotesPerMeasure = numSixteenthNotes;
		ticksPerMeasure = numSixteenthNotes * 240 * 4;
	}

	void applySixteenthSkip(double *total_start, double *total_end,
		double *mod_end, double *mod_start, double tickInc)
	{
		*total_start = midiTicksElapsed - tickInc;
		*total_end = midiTicksElapsed;

		*mod_end = midiTicksElapsed
			- (int)(midiTicksElapsed / 15360) * 15360;
		*mod_start = *mod_end - tickInc;

		int ticksPerBar = 240 * sixteenthNotesPerMeasure;
		int presentBarNum = (int)*mod_end / 3840;
		double ticksElapsed_MOD = *mod_end - presentBarNum * 3840;
		if (ticksElapsed_MOD > ticksPerBar)
		{
			midiTicksElapsed += (3840 - ticksPerBar);
			*total_start = midiTicksElapsed - tickInc;
			*total_end = midiTicksElapsed;

			*mod_start += (3840 - ticksPerBar);
			*mod_end += (3840 - ticksPerBar);
			
			*mod_end = midiTicksElapsed
				- (int)(midiTicksElapsed / 15360) * 15360;
			*mod_start = *mod_end - tickInc;
		}
	}

	void setChord_Inbuilt(short boxIndex, short chordDegree)
	{
		currentMusic.presentChords[boxIndex - 1] = chordDegree;
		int noteDegrees[4] = { 
			chordDegree + scaleTonicTrans.chordTypes_DegreeIntervals[currentMusic.presentChordsType][0], 
			chordDegree + scaleTonicTrans.chordTypes_DegreeIntervals[currentMusic.presentChordsType][1],
			chordDegree + scaleTonicTrans.chordTypes_DegreeIntervals[currentMusic.presentChordsType][2],
			chordDegree + scaleTonicTrans.chordTypes_DegreeIntervals[currentMusic.presentChordsType][3]
		};
		int noteNums[4] = { 0, 0, 0, 0 };
		for (int i = 0; i < 4; i++)
			noteNums[i] = scaleTonicTrans.getMidiKeyFromDegree(noteDegrees[i], scaleID_ORIG, tonicOffset_ORIG);
		int sixteenthTicks = 240;
		int noteLength_Chord = 1920;
		int noteLength_Bass = 60;

		int checkBounds_START = noteLength_Chord * (boxIndex - 1);
		int checkBounds_END = noteLength_Chord * (boxIndex);
		int eventTimeStamp = 0;
		int eventType = 0;
		int currentVoice = 0;

		// CHORD TRACK
		for (int i = 0; i < currentMusic.midiTracks[1].numEvents; i++)
		{
			eventTimeStamp = currentMusic.midiTracks[1].infoMatrix[i][3];
			eventType = currentMusic.midiTracks[1].infoMatrix[i][0];
			// NOTE ONS
			if ((eventTimeStamp % (4 * noteLength_Chord) == checkBounds_START) && eventType == 1)
			{
				currentMusic.midiTracks[1].infoMatrix[i][1] = noteNums[currentVoice];
				currentVoice = (currentVoice + 1) % 4;
			}
			// NOTE OFFS
			if ((eventTimeStamp % (4 * noteLength_Chord) == checkBounds_END) && eventType == 2)
			{
				currentMusic.midiTracks[1].infoMatrix[i][1] = noteNums[currentVoice];
				currentVoice = (currentVoice + 1) % 4;
			}
		}

		// BASSLINE
		for (int i = 0; i < currentMusic.midiTracks[2].numEvents; i++)
		{
			eventTimeStamp = currentMusic.midiTracks[2].infoMatrix[i][3];
			eventType = currentMusic.midiTracks[2].infoMatrix[i][0];
			if ((eventTimeStamp % (4 * noteLength_Chord) >= checkBounds_START) &&
				(eventTimeStamp % (4 * noteLength_Chord) < checkBounds_END) &&
				(eventType == 1))
			{
				currentMusic.midiTracks[2].infoMatrix[i][1] = noteNums[0];
				currentMusic.midiTracks[2].infoMatrix[i + 1][1] = noteNums[0];
			}
		}
	}
};