#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class UIStrings
{
public:

	String screenHeaders[9] =
	{
		"Introduction",
		"Participant Details",
		"Goal of Session",
		"Goal of Block",
		"Training Phase",
		"Testing Phase",
		"Subjective Ratings",
		"End of Experiment",
		""
	};

	String warnings[8] =
	{
		"",
		"Please fill in all fields to continue.",
		"",
		"",
		"",
		"",
		"",
		""
	};

	String welcomeText =
		"Welcome. Your task is to find a target point on a horizontal line"
		" using sound. \n \n" "The goal of the experiment is to compare "
		"the guidance capabilities of different sound strategies.";

	String detailedInstructions =
		"The experiment has 3 sessions - SPEED, PRECISION and TARGET OVERSHOOTS. \n"
		"In each session, there are 10 blocks - each contains ONE sound guidance strategy. \n\n"
		"Each block has a training phase and FOUR tests where you must locate a random target."
		"You must then rate the aesthetic qualities of that strategy (e.g. pleasantness). \n\n"
		"There are FIVE musical strategies and FIVE non-musical strategies. \n"
		"All sessions and blocks are presented in a random order";


	String timeElapsedTotal =
		"Total Time: ";

	String session_Current =
		"Current Session: ";

	String block_Current =
		"Current Block: ";

	String trial_Current =
		"Current Trial: ";

	String targetRangeText =
		"THE TARGET LIES IN THIS AREA";

	String isTraining =
		"This is the training phase, where you can try to find a target as many times as you like.";

	String isTrial =
		"Your responses are now being recorded (FOUR in total).";

	// FILLING IN PERSONAL DETAILS
	String participant_Name = "Name";
	String participant_Age = "Age";
	String participant_Gender = "Please specify your gender:";
	String participant_Gender_Options[4] =
	{
		"Male",
		"Female",
		"Other",
		"Rather not say"
	};
	String participant_HearingLoss = "Do you suffer from any hearing loss that you are aware of?";
	String participant_HearingLoss_Options[3] =
	{
		"None",
		"Mild to Moderate",
		"Severe"
	};

	String participant_Handedness = "Are you left-handed or right-handed (when using a mouse)?";
	String participant_Handedness_Options[2] = 
	{
		"Left",
		"Right"
	};

	String continueText_Screenwise[10] =
	{
		"Press SPACE to begin the experiment.",
		"Press SPACE to commence the first session.",
		"Press SPACE to begin the session.",
		"Press SPACE to begin the training phase.",
		"Press SPACE to begin the testing phase.",
		"Press SPACE when you have located the target.",
		"Press SPACE to begin the next block.",
		"Press SPACE to conclude the experiment.",
		"Get Ready!",
		"Press SPACE to start filling in your details."
	};


	String session_Instructions[3] =
	{
		"Find the target as FAST as possible. \n\n NOTE that there is a time limit of 5 SECONDS.",
		"Find the target as PRECISELY as possible. \n\n There is no time limit.",
		"Find the target WITHOUT PASSING IT. \n\n There is no time limit."
	};

	String block_Names[10] =
	{
		"The target is the point where the WAVE PITCH is MINIMUM.",
		"The target is the point where the BEEP TEMPO is MAXIMUM.",
		"The target is the point where the BEEPS are SYNCHRONIZED.",
		"The target is the point where the WAVE sounds most PLEASANT.",
		"The target is the point where the NOISE BRIGHTNESS is MAXIMUM.",
		"The target is the point where the MELODY PITCH is MAXIMUM.",
		"The target is the point where the MUSIC TEMPO is MAXIMUM.",
		"The target is the point where the INSTRUMENTS are SYNCHRONIZED.",
		"The target is the point where the MUSIC sounds most PLEASANT.",
		"The target is the point where the MUSIC BRIGHTNESS is MAXIMUM."
	};

	String block_tutorial_URLs[10] = 
	{
		"www.google.com",
		"www.google.com",
		"www.google.com",
		"www.google.com",
		"www.google.com",
		"www.google.com",
		"www.google.com",
		"www.google.com",
		"www.google.com",
		"www.google.com"
	};

	String pleasantnessText =
		"I found the auditory guidance to be pleasant to listen to. \n (1 = Strongly Disagree // 7 = Strongly Agree)";

	String longevityText =
		"I would be prepared to use this form of guidance for a long period of time (a.k.a. hours). \n (1 = Strongly Disagree // 7 = Strongly Agree)";

	String thankYou =
		"Thank you very much for participating in this experiment. Have a nice day!";

};