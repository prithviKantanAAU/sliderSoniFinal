#pragma once

class ExperimentControl
{
public:

	// Session Indices: 1: FAST // 2: PRECISE // 3: MIN OVERSHOOTS
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

	// UI Status
	//  0: Pre Expt Start Screen
	//  1: Personal Details Screen
	//  2: Session Intro Screen
	//  3: Block Intro/Instruction Screen
	//  4: Training Screen
	//  5: Trial Screen
	//  6: Subjective Data Screen
	//  7: Conclusion Screen

	int idx_Screen = 0;
};
