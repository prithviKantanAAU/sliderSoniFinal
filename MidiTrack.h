#pragma once
class MidiTrack
{
public:
	MidiTrack() {};
	~MidiTrack() {};
	void resetPlayback() 
	{ Idx_nextEvent = 0; };
	int numEvents = 0;
	bool isEventNoteOn[5000] = { false };
	int infoMatrix[5000][4] = { 0 };	// Type - Val - Vel - TS
	void flush_infoMatrix()
	{
		for (int i = 0; i < 5000; i++)
		{
			isEventNoteOn[i] = false;
			for (int j = 0; j < 4; j++)
				infoMatrix[i][j] = 0;
		}
	}
	int Idx_nextEvent = 0;			
	void incrementEventsHandled(int ticksPerMeasure) 
	{
		Idx_nextEvent++; 
		while (infoMatrix[Idx_nextEvent][0] == 0)
			Idx_nextEvent++;
		// HANDLE TIME SIGNATURE

		int timeStamp_nextEvent = infoMatrix[Idx_nextEvent][3];
		int timeStamp_nextEvent_MOD = timeStamp_nextEvent % 3840;
		while (timeStamp_nextEvent_MOD >= ticksPerMeasure / 4)
		{
			Idx_nextEvent++;
			timeStamp_nextEvent = infoMatrix[Idx_nextEvent][3];
			timeStamp_nextEvent_MOD = timeStamp_nextEvent % 3840;
		}
		
	}
};

