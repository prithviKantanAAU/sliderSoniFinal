#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ExperimentLogStore
{
public:
	ExperimentLogStore()
	{
	};
	ExperimentLogStore() {};

	File exptLog;
	File trajectories_S1;
	File trajectories_S2;
	File trajectories_S3;

	void createAndConfigFile()
	{

	};

	void saveLog()
	{

	};
};