#pragma once

class ExperimentControl
{
public:

	short session_Total = 3;
	short session_CurrentIdx = 0;
	short session_Completed = 0;

	short block_Total = 10;
	short block_CurrentIdx = 0;
	short block_Completed = 0;

	short trial_Total = 4;
	short trial_Current = 0;

	void beginSession()
	{
	}

	void concludeSession()
	{
	}

	void beginBlock()
	{
	}

	void concludeBlock()
	{
	}

	void beginTrial()
	{
	}

	void concludeTrial()
	{
	}
};
