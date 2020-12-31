#pragma once
#include "ExperimentLogStore.h"
#include "participantDetails.h"
#include "Sequencer.h"
#include "FaustStrings_AP.h"
#include "audioParamInfo.h"

class ExperimentControl
{
public:

	ExperimentControl()
	{
		for (int t = 0; t < trial_Total; t++)
		{
			for (int b = 0; b < block_Total; b++)
			{
				for (int s = 0; s < session_Total; s++)
				{
					expt_targets[t][b][s] = 0;
					expt_error[t][b][s] = 0;
					expt_time[t][b][s] = 0;
					expt_overshoots[t][b][s] = 0;
					rating_pleasantness[b][s] = 4;
					rating_longevity[b][s] = 4;
				}

				for (int w = 0; w < 10000; w++)
				{
					trajectory_sliderPos_FAST[t][b][w] = 0;
					trajectory_sliderPos_PRECISE[t][b][w] = 0;
					trajectory_sliderPos_OVERSHOOT[t][b][w] = 0;
				}
			}
		}

		populateGrooves();
		sequencer.currentMusic.finalTimeStamp = 100000;
	};

	ParticipantDetails participantDetails;
	ExperimentLogStore exptLogStore;
	Sequencer sequencer;
	FaustStrings_AP apStrings;
	audioParamInfo audioParams;

	int screensElapsed = 0;
	float totalScreens = 196;
	double overallProgress = 0.0;
	std::string apString = "";
	// Session Indices: 0: FAST // 1: PRECISE // 2: MIN OVERSHOOTS
	short session_Total = 3;											// 0 - 1 - 2
	short session_CurrentIdx = 0;
	short session_Completed = 0;
	short session_Completed_Idx[3] = {-1,-1,-1};
	short session_Order[3] = { -1,-1,-1 };

	short block_Total = 10;												// 0 - 1 - 9
	short block_CurrentIdx = 0;
	short block_Completed = 0;
	short block_Order[3][10] = 
	{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	};
	short block_Completed_Idx[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	short trial_Total = 4;
	short trial_Current = 0;											// 0 - 1 - 2 - 3

	double timeElapsed_SEC_FLOAT = 0;
	double timeElapsed_presentScreen = 0;
	double time_minOnScreen = 0.5;
	int timeElapsed_MIN = 0;
	int timeElapsed_SEC = 0;
	double timeRemaining = 0;
	double countInTimeLeft = 0;
	double countInTimeMax = 3;
	double timeTotal_Sessionwise[3] = { 5, 100000, 100000 };
	void decrementTimeRemaining(double dec)
	{
		if (session_CurrentIdx == 0 && isTrialON)
		timeRemaining -= dec;
		timeRemaining = fmax(0, timeRemaining);

		if (idx_Screen == 8)
			countInTimeLeft -= dec;
	};

	// MEASUREMENTS
	bool isTrainingON = false;
	bool isTrialON = false;
	float val_taskSlider = 0;

	// TRIAL-WISE MEASURES
	float expt_targets[4][10][3];
	float expt_error[4][10][3];
	float expt_time[4][10][3];
	float expt_overshoots[4][10][3];
	float expt_target_presentTrial = 0.0;
	float expt_error_presentTrial = 0.0;
	float expt_error_presentTrial_z1 = 0.0;
	float expt_time_presentTrial = 0.0;
	float expt_overshoots_presentTrial = 0.0;

	// TRAJECTORY MEASURES
	int	  trajectory_writeIdx = 0;
	float trajectory_sliderPos_FAST[4][10][10000];
	float trajectory_sliderPos_PRECISE[4][10][10000];
	float trajectory_sliderPos_OVERSHOOT[4][10][10000];

	// BLOCK-WISE RATINGS
	float rating_pleasantness_presentTrial = 4;
	float rating_longevity_presentTrial = 4;
	float rating_pleasantness[10][3];
	float rating_longevity[10][3];

	void beginSession()
	{
		session_CurrentIdx = session_Order[session_Completed];
		idx_Screen = 2;
		block_Completed = 0;
	}

	void beginBlock()
	{
		block_CurrentIdx = block_Order[session_CurrentIdx][block_Completed];

		apString = (apStrings.baseName + apStrings.SonificationNames[block_CurrentIdx]).toStdString();
		sequencer.soni_AP_Name = audioParams.audioParam_ObjectArray[block_CurrentIdx].name;
		idx_Screen = 3;
	}

	void beginTraining()
	{
		isTrainingON = true;
		getNewTargetValue();
		sequencer.stopMusic();
		loadRandomMusicFile();
		resetAndConfigureAP();
	}

	void beginTrial()
	{
		expt_error_presentTrial = 0;
		expt_time_presentTrial = 0;
		expt_overshoots_presentTrial = 0;
		trajectory_writeIdx = 0;
		isTrialON = true;
		getNewTargetValue();
		expt_targets[trial_Current][block_CurrentIdx][session_CurrentIdx] = expt_target_presentTrial;
		timeRemaining = timeTotal_Sessionwise[session_CurrentIdx];
		sequencer.stopMusic();
		loadRandomMusicFile();
		resetAndConfigureAP();
	}

	void mapTargetDistance()
	{
		expt_error_presentTrial = (val_taskSlider - expt_target_presentTrial) * 100;
		checkOvershoot(expt_error_presentTrial);
		expt_error_presentTrial_z1 = expt_error_presentTrial;
		expt_error_presentTrial = fabs(expt_error_presentTrial);

		// APPLY MAPPING FUNCTION IF NECESSARY
		float mapOrder = audioParams.audioParam_ObjectArray[block_CurrentIdx].mappingOrder;
		float apVal_Final = pow(expt_error_presentTrial / 100.0, mapOrder);
		
		if (expt_error_presentTrial < 0.2)
			apVal_Final = 0;

		// MAP DSPFAUST
		if (audioParams.audioParam_ObjectArray[block_CurrentIdx].type == 1)
		sequencer.dspFaust.setParamValue(apString.c_str(), apVal_Final);

		else
		{
			if (audioParams.audioParam_ObjectArray[block_CurrentIdx].name == "M_Tempo")
				sequencer.tempoTickInc.ap_forSkew_1D = pow(1 - expt_error_presentTrial / 100.0, mapOrder);

			if (audioParams.audioParam_ObjectArray[block_CurrentIdx].name == "M_Pitch")
				sequencer.AP_Val = pow(1 - expt_error_presentTrial / 100.0, mapOrder);
		}
	}

	void checkOvershoot(float currentError)
	{
		if (currentError * expt_error_presentTrial_z1 < 0)
			expt_overshoots_presentTrial++;
	}

	// CONCLUDE PRESENT TRIAL
	void endTrial()
	{
		sequencer.stopMusic();
		val_taskSlider = 0;
		// STORE Error, Time, Overshoots
		expt_error[trial_Current][block_CurrentIdx][session_CurrentIdx] = expt_error_presentTrial;
		expt_overshoots[trial_Current][block_CurrentIdx][session_CurrentIdx] = expt_overshoots_presentTrial;
		expt_time[trial_Current][block_CurrentIdx][session_CurrentIdx] = expt_time_presentTrial;

		expt_error_presentTrial = 0;
		expt_time_presentTrial = 0;
		expt_overshoots_presentTrial = 0;

		trial_Current++;
		// INCREMENT Trial Num
		if (trial_Current <= (trial_Total - 1))
		{
			if (session_CurrentIdx == 0)
			{
				countInTimeLeft = countInTimeMax;
				idx_Screen = 8;
			}

			else
			{
				beginTrial();
			}
		}
		else
		{
			sequencer.stopMusic();
			isTrialON = false;
			idx_Screen = 6;
		}
		trial_Current %= trial_Total;
	}

	void updateCompletedBlock()
	{
		
	}

	// CONCLUDE PRESENT BLOCK
	void endBlock()
	{
		// STORE pleasantness, longevity
		rating_pleasantness[block_CurrentIdx][session_CurrentIdx] = rating_pleasantness_presentTrial;
		rating_longevity[block_CurrentIdx][session_CurrentIdx] = rating_longevity_presentTrial;
		
		// Find next block index
		trial_Current = 0;
		block_Completed++;
		if (block_Completed < block_Total)
		{
			block_CurrentIdx = block_Order[session_CurrentIdx][block_Completed];
			beginBlock();
		}
		else
		{
			endSession();
		}

	}

	// CONCLUDE PRESENT SESSION
	void endSession()
	{
		session_Completed++;
		
		for (int i = 0; i < block_Total; i++) block_Completed_Idx[i] = -1;			// RESET ELAPSED BLOCKS
		// Find next session index
		if (session_Completed < session_Total)		beginSession();
		else
		{
			createAndConfigFile();
			saveLog_EXPT();
			saveLog_TRAJ();
			idx_Screen = 7;
		}
	}

	// CALL ONCE EVERY 20 ms
	void storeSliderTrajectoryVal()
	{
		if (isTrialON)
		{
			switch (session_CurrentIdx)
			{
			case 0:
				trajectory_sliderPos_FAST[trial_Current][block_CurrentIdx][trajectory_writeIdx] = val_taskSlider;
				break;
			case 1:
				trajectory_sliderPos_PRECISE[trial_Current][block_CurrentIdx][trajectory_writeIdx] = val_taskSlider;
				break;
			case 2:
				trajectory_sliderPos_OVERSHOOT[trial_Current][block_CurrentIdx][trajectory_writeIdx] = val_taskSlider;
				break;
			}
			trajectory_writeIdx++;
		}
	}

	void updateTimeVariables(double incrementSec)
	{
		timeElapsed_SEC_FLOAT += incrementSec;
		timeElapsed_presentScreen += incrementSec;
		int seconds_Int = (int)timeElapsed_SEC_FLOAT;
		timeElapsed_MIN = seconds_Int / 60;
		timeElapsed_SEC = seconds_Int % 60;
		if (isTrialON)
			expt_time_presentTrial += incrementSec;
	}

	// UI Status
	//  0: Pre Expt Start Screen
	//  1: Personal Details Screen
	//  2: Session Intro Screen
	//  3: Block Intro/Instruction Screen
	//  4: Training Screen
	//  5: Trial Screen
	//  6: Subjective Data Screen
	//  7: Conclusion Screen
	//  8: Count In Screen

	int idx_Screen = 0;

	// IN-TRIAL HELPER FUNCTIONS

	void generateExptOrder()
	{
		// SESSION

		for (int i = 0; i < session_Total; i++)
		{
			session_Order[i] = getNewRandomIndex(session_Total, i, session_Order);

			// BLOCKS
			for (int j = 0; j < block_Total; j++)
			{
				block_Order[i][j] = getNewRandomIndex(block_Total, j, block_Order[i]);
			}
			/*block_Order[i][0] = 8;									/// To Test Strategies
			session_Order[0] = 1;*/
		}
 	}

	Random randGen;
	int getNewRandomIndex(int total, int totalElapsed, short *elapsedIndices)
	{
		int randomIndex = randGen.nextInt(total);
		bool alreadyDone = false;

		for (int i = 0; i < total; i++)
		{
			if (randomIndex == elapsedIndices[i])
				alreadyDone = true;
		} //Check if already done

		while (alreadyDone)
		{
			randomIndex = randGen.nextInt(total);
			alreadyDone = false;
			for (int i = 0; i < total; i++)
			{
				if (randomIndex == elapsedIndices[i])
					alreadyDone = true;
			}
		}
		
		elapsedIndices[totalElapsed] = randomIndex;
		return randomIndex;
	}

	void getNewTargetValue()
	{
		int valuePre = randGen.nextInt(30);
		expt_target_presentTrial = (float)(50 + valuePre) / 100.0;
		mapTargetDistance();
	}

	void handlePlayback()
	{
		if (isTrialON || isTrainingON)
		{
			// INCREMENT BASIC PLAYBACK COUNTERS
			sequencer.timeElapsed_SONG += 0.001;
			double tickInc = sequencer.tempoTickInc.getNewTickIncrement(
				sequencer.midiTicksElapsed, sequencer.currentMusic.finalTimeStamp, sequencer.ticksPerMS);
			sequencer.midiTicksElapsed += tickInc;
			sequencer.tapTempoCounter = min(1, sequencer.tapTempoCounter + 0.001);		// Limit to 1

			// RUN MUSICAL CLOCK CALLBACK
			clockCallback(tickInc);

			// STOP MUSIC IF SONG COMPLETE
			if (sequencer.getSongProgress())
				sequencer.stopMusic();
		}
	}

	void clockCallback(double tickInc)
	{
		// IF CLOCK PULSE DUE, TRIGGER CLOCK
		if (checkIfPulseDue())
			triggerClock();

		// CHECK FOR NEW MIDI EVENTS, HANDLE IF NEEDED
		sequencer.check_Handle_New_MIDIEvents(tickInc);

		// UPDATE MUSIC PHASE
		sequencer.musicPhase.updatePhase(tickInc);
	}

	void triggerClock()
	{
		sequencer.incrementPulseCounter();
		sequencer.lastPulseTime = sequencer.nextPulseTime;
		sequencer.nextPulseTime += sequencer.midiTickIncrement;
	}

	bool checkIfPulseDue()
	{
		return (sequencer.midiTicksElapsed >= sequencer.nextPulseTime);
	};

	void populateGrooves()
	{
		File forAppDirectory;
		String appPath = forAppDirectory.getSpecialLocation(File::currentApplicationFile).getFullPathName();
		appPath = appPath.upToLastOccurrenceOf("\\", true, false);
		appPath += "MIDI Drum Library\\Base\\";
		sequencer.currentMusic.populateStyles(appPath);
	}

	void resetAndConfigureAP()
	{
		std::string apString_TEMP = "";
	
		for (int i = 0; i < audioParams.num_audioParams; i++)
		{
			// RESET FAUST APs
			apString_TEMP = (apStrings.baseName + apStrings.SonificationNames[block_CurrentIdx]).toStdString();
			sequencer.dspFaust.setParamValue(apString_TEMP.c_str(), 0);
			
			// RESET JUCE APs
			sequencer.tempoTickInc.ap_forSkew_1D = 1;
			sequencer.AP_Val = expt_error_presentTrial / 100.0;
		}

		//CHOOSE WHETHER TRADITIONAL OR MUSICAL
		if (block_CurrentIdx < 5)
		{
			sequencer.dspFaust.setParamValue(apStrings.tradSoniToggle.toStdString().c_str(), 1);
			sequencer.dspFaust.setParamValue(apStrings.tradSoniChoice.toStdString().c_str(), block_CurrentIdx);
		}

		else
		{
			sequencer.dspFaust.setParamValue(apStrings.tradSoniToggle.toStdString().c_str(), 0);
			sequencer.dspFaust.setParamValue(apStrings.tradSoniChoice.toStdString().c_str(), 0);
		}
		//CHOOSE AP INDEX
		//SET AP VALUE INITIALLY
		mapTargetDistance();
	}

	void loadRandomMusicFile()
	{
		String path = "";
		String appPath = "";
		File forAppDirectory;
		int randomInbuiltIdx = 0;
		if (audioParams.audioParam_ObjectArray[block_CurrentIdx].name == "M_Pitch")
		{
			sequencer.musicMode = 3;
			appPath = forAppDirectory.getSpecialLocation
			(File::currentApplicationFile).getFullPathName().upToLastOccurrenceOf("\\", false, true)
				+ "\\MIDI Inbuilt Library\\";
			randomInbuiltIdx = 1 + randGen.nextInt(4);
		}

		else
		{
			sequencer.musicMode = 1;
			appPath = forAppDirectory.getSpecialLocation
			(File::currentApplicationFile).getFullPathName().upToLastOccurrenceOf("\\", false, true)
				+ "\\MIDI Library\\";
		}
		File currentFile;

		auto dir_Base = File(appPath);
		int numSongs = dir_Base.getNumberOfChildFiles(2, "*.mid");
		auto songFiles_Base = dir_Base.findChildFiles(2, false, "*.mid");
		songFiles_Base.sort();
		int randomSongIdx = randGen.nextInt(numSongs);
		currentFile = songFiles_Base.getUnchecked(randomSongIdx);

		if (audioParams.audioParam_ObjectArray[block_CurrentIdx].name == "M_Pitch")
			path = appPath + "\\"+ String(randomInbuiltIdx) +".mid";

		else
			path = appPath + "\\" + currentFile.getFileNameWithoutExtension() + ".mid";

		sequencer.loadNewFile_MIDI(path);
		sequencer.togglePlayPause();
		setTempo(setRandomTempo());
	}

	float setRandomTempo()
	{
		return 80 + randGen.nextInt(50);
	}

	void setTempo(float value)
	{
		sequencer.tempo = value;
		double intervalMs = 60000 / sequencer.tempo * 0.25;
		double intervalMultiplier = sequencer.isTripletMode ? 4.0 / 3.0 : 1.0;
		sequencer.ticksPerMS = 960 / (4 * intervalMs) * intervalMultiplier;
		sequencer.dspFaust.setParamValue(sequencer.faustStrings.Tempo.c_str(), value);
		sequencer.musicPhase.setPhaseInc(sequencer.tempo, 1000);
	};

	void createAndConfigFile()
	{
		exptLogStore.filePath_EXPT = exptLogStore.
			forRootDirectory.getSpecialLocation(File::currentApplicationFile).getFullPathName();
		exptLogStore.filePath_EXPT = exptLogStore.filePath_EXPT.upToLastOccurrenceOf("\\", true, false);
		exptLogStore.filePath_EXPT += participantDetails.name + " - " + exptLogStore.getCurrentTime();

		exptLogStore.filePath_EXPT_LOG = exptLogStore.filePath_EXPT + "\\Measurements.csv";
		exptLogStore.filePath_TRAJ1 = exptLogStore.filePath_EXPT + "\\Trajectories - S1.csv";
		exptLogStore.filePath_TRAJ2 = exptLogStore.filePath_EXPT + "\\Trajectories - S2.csv";
		exptLogStore.filePath_TRAJ3 = exptLogStore.filePath_EXPT + "\\Trajectories - S3.csv";

		CreateDirectory(exptLogStore.filePath_EXPT.toStdString().c_str(), NULL);
		exptLogStore.fileObj[0] = fopen(exptLogStore.filePath_EXPT_LOG.toStdString().c_str(), "w");
		exptLogStore.fileObj[1] = fopen(exptLogStore.filePath_TRAJ1.toStdString().c_str(), "w");
		exptLogStore.fileObj[2] = fopen(exptLogStore.filePath_TRAJ2.toStdString().c_str(), "w");
		exptLogStore.fileObj[3] = fopen(exptLogStore.filePath_TRAJ3.toStdString().c_str(), "w");
	};

	void saveLog_EXPT()
	{
		String data = "";
		bool isSubjRatingDuplicate = false;

		// Participant Metadata
		data = participantDetails.name + "," + participantDetails.age + "," + participantDetails.hearingLoss
			+ "," + participantDetails.hand + ",";
		exptLogStore.save_Expt_LogLine(data);

		for (int s = 0; s < session_Total; s++)							// FOR EACH SESSION
		{
			data = exptLogStore.names_Sessions[s] + ",";
			exptLogStore.save_Expt_LogLine(data);

			for (int v = 0; v < 5; v++)									// FOR EACH VARIABLE
			{
				data = exptLogStore.names_Variables[v] + ",";
				exptLogStore.save_Expt_LogLine(data);

				for (int t = 0; t < trial_Total; t++)					// FOR EACH TRIAL
				{
					data = "";
					for (int b = 0; b < block_Total; b++)				// FOR EACH BLOCK
					{
						switch (v)
						{
						case 0:
							data += String(expt_error[t][b][s]) + ",";
							break;
						case 1:
							data += String(expt_time[t][b][s]) + ",";
							break;
						case 2:
							data += String(expt_overshoots[t][b][s]) + ",";
							break;
						case 3:
							data += String(rating_pleasantness[b][s]) + ",";
							break;
						case 4:
							data += String(rating_longevity[b][s]) + ",";
							break;
						}
					}
					isSubjRatingDuplicate = (v > 2 && t > 0);
					if (!isSubjRatingDuplicate) 
						exptLogStore.save_Expt_LogLine(data);
				}
			}
		}
		fclose(exptLogStore.fileObj[0]);
	};

	void saveLog_TRAJ()
	{
		float minTime = 0;
		float maxTime = 0;
		exptLogStore.minMax(expt_time, &minTime, &maxTime);
		int numTrajSamples = maxTime * 50;
		String data = "";
		// OPEN FILE

		for (int s = 0; s < session_Total; s++)							// FOR EACH SESSION
		{
			for (int b = 0; b < block_Total; b++)						// FOR EACH BLOCK
			{
				// Block Header
				data += "Block " + String(b + 1) + ",,,,";
			}
			
			exptLogStore.save_Traj_LogLine(s, data);
			data = "";

			// TRIAL IDX
			for (int b = 0; b < block_Total; b++)						// FOR EACH BLOCK
			{
				for (int t = 0; t < trial_Total; t++)					// FOR EACH TRIAL
				{
					data += String(t + 1) + ",";
				}
			}

			exptLogStore.save_Traj_LogLine(s, data);
			data = "";

			// TARGETS
			for (int b = 0; b < block_Total; b++)						// FOR EACH BLOCK
			{
				for (int t = 0; t < trial_Total; t++)					// FOR EACH TRIAL
				{
					data += String(expt_targets[t][b][s]) + ",";
				}
			}

			exptLogStore.save_Traj_LogLine(s, data);
			data = "";

			for (int idx = 0; idx < numTrajSamples; idx++)					// STORING EACH SAMPLE (ROW)
			{
				for (int b = 0; b < block_Total; b++)					// FOR EACH BLOCK
				{
					for (int t = 0; t < trial_Total; t++)				// FOR EACH TRIAL
					{
						switch (s)
						{
						case 0:
							data += String(trajectory_sliderPos_FAST[t][b][idx]) + ",";
							break;
						case 1:
							data += String(trajectory_sliderPos_PRECISE[t][b][idx]) + ",";
							break;
						case 2:
							data += String(trajectory_sliderPos_OVERSHOOT[t][b][idx]) + ",";
							break;
						}
					}
				}
				exptLogStore.save_Traj_LogLine(s, data);
				data = "";
			}
			// CLOSE FILE
			fclose(exptLogStore.fileObj[s + 1]);
		}

		
	}
};