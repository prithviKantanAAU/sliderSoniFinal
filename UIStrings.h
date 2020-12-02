#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class UIStrings
{
public:
	
	String screenHeaders[8] =
	{
		"Introduction",
		"Participant Details",
		"Goal of Session",
		"Goal of Block",
		"Training Phase",
		"Testing Phase",
		"Subjective Ratings",
		"End of Experiment"
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
	"Welcome. Your task is to find a point on a horizontal line" 
		" using different audio guidance types. \n \n" "Next, you will be asked to rate their "
		"aesthetic qualities.";

	String timeElapsedTotal =
		"Total Time: ";

	String session_Current =
		"Current Session: ";

	String block_Current =
		"Current Block: ";

	String trial_Current =
		"Current Trial: ";

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
		"Mild/Moderate",
		"Severe"
	};

	String participant_Handedness = "Are you left-handed or right-handed (when using a mouse)?";
	String participant_Handedness_Options[2] = 
	{
		"Left",
		"Right"
	};

	String continueText_Screenwise[8] =
	{
		"Press SPACE to begin the experiment.",
		"Press SPACE to proceed.",
		"Press SPACE to begin the session.",
		"Press SPACE to begin the training phase.",
		"Press SPACE to begin the testing phase (time starts immediately).",
		"Press SPACE when you have located the target.",
		"Press SPACE to proceed.",
		"Press SPACE to conclude the experiment."
	};


	String session_Instructions[3] =
	{
		"Find the target as FAST as possible.",
		"Find the target as PRECISELY as possible.",
		"Find the target WITHOUT PASSING IT."
	};

	String block_Names[10] =
	{
		"Block Name #1",
		"Block Name #2",
		"Block Name #3",
		"Block Name #4",
		"Block Name #5",
		"Block Name #6",
		"Block Name #7",
		"Block Name #8",
		"Block Name #9",
		"Block Name #10"
	};

	String block_Instructions[10] =
	{
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		""
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