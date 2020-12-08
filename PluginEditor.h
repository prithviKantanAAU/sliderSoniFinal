#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "UIStrings.h"

class SliderSonificationFinalAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    SliderSonificationFinalAudioProcessorEditor (SliderSonificationFinalAudioProcessor&);
    ~SliderSonificationFinalAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    SliderSonificationFinalAudioProcessor& processor;
	UIStrings uiStrings;
	void configureUI_Initial();
	void getNextScreenIdx();
	void toggleScreen(short newScreenIdx);
	void timerCallback();
	void updateExptLabels()
	{
		timeElapsed_Total.setText
		(
			uiStrings.timeElapsedTotal + 
			String(processor.experimentControl.timeElapsed_MIN) + " min " +
			String(processor.experimentControl.timeElapsed_SEC) + " sec"
			,dontSendNotification
		);

		session_Present.setText
		(
			uiStrings.session_Current +
			//String(processor.experimentControl.session_Completed + 1)
			String(processor.experimentControl.session_CurrentIdx + 1)
			,dontSendNotification
		);

		block_Present.setText
		(
			uiStrings.block_Current +
			//String(processor.experimentControl.block_Completed + 1)
			String(processor.experimentControl.block_CurrentIdx + 1)
			,dontSendNotification
		);

		trial_Present.setText
		(
			uiStrings.trial_Current +
			String(processor.experimentControl.trial_Current + 1),
			dontSendNotification
		);

		if (processor.experimentControl.idx_Screen == 4)
		{
			if (processor.experimentControl.expt_error_presentTrial < 1)
				targetFound.setVisible(true);
			else  targetFound.setVisible(false);
		}

		exptProgress_Var = processor.experimentControl.overallProgress;
	}

	void updateContinuePrompt(int screenIdx)
	{
		continuePrompt.setVisible(true);
		continuePrompt.setText
		(
			uiStrings.continueText_Screenwise[screenIdx]
			, dontSendNotification
		);
	}

	void updateTimeRemaining()
	{
		if (processor.experimentControl.idx_Screen == 5)
		{
			if (processor.experimentControl.session_CurrentIdx == 0)
			{
				timeRemaining.setVisible(true);
				timeRemaining.setText(
					"Remaining Time: " + String((int)(processor.experimentControl.timeRemaining + 0.99)) + " sec"
					, dontSendNotification
				);
			}
			else timeRemaining.setVisible(false);
		}

		if (processor.experimentControl.idx_Screen == 8)
		{
			countIn.setText(
				String((int)(processor.experimentControl.countInTimeLeft + 0.99)), 
				dontSendNotification
			);
		}
	};

	// Permanently Visible Elements
	// Testing
	Slider toggleScreenIdx;
	int screenIdx_z1 = 0;
	int trialIdx_z1 = 0;
	Label screenHeader;
	Label warning;
	ProgressBar exptProgress;
	double exptProgress_Var = 0.0;

	// Time Monitoring
	Label timeElapsed_Total;

	// Experiment Monitoring
	Label session_Present;
	Label block_Present;
	Label trial_Present;

	// Continue Prompt
	Label continuePrompt;

	// Screen 0
	Label welcomeText;

	// Screen 1
	TextEditor		participant_Name;
	Label			participant_Name_Label;
	TextEditor		participant_Age;
	Label			participant_Age_Label;
	ToggleButton	participant_Gender[4];
	Label			participant_Gender_Label;
	Label			participant_Gender_Options_Labels[4];
	ToggleButton	participant_HearingLoss[3];
	Label			participant_HearingLoss_Label;
	Label			participant_HearingLoss_Options_Labels[3];
	ToggleButton	participant_Handedness[2];
	Label			participant_Handedness_Label;
	Label			participant_Handedness_Options_Labels[2];

	// UI Status
	//  0: Pre Expt Start Screen
	//  1: Personal Details Screen
	//  2: Session Intro Screen
	//  3: Block Intro/Instruction Screen
	//  4: Training Screen
	//  5: Trial Screen
	//  6: Subjective Data Screen
	//  7: Conclusion Screen

	// Screen 2
	Label sessionDescription;

	// Screen 3
	Label blockDescription;
	HyperlinkButton blockTutorialLink;
	void updateTutorialURL(int blockIdx)
	{
		blockTutorialLink.setURL(uiStrings.block_tutorial_URLs[blockIdx]);
	};

	// Screen 4
	Label trainingMessage;
	TextButton resetTarget;
	Label targetFound;

	// Screen 5
	Label timeRemaining;
	Label testingMessage;

	// Screen 6
	Label pleasantnessLabel;
	Slider pleasantness;
	Label longevityLabel;
	Slider longevity;

	// Screen 7
	Label thankYou;

	// Data Collection
	Slider task;

	// Screen 8
	Label countIn;

	void hideScreenSpecificUI()
	{
		// Screen 0
		welcomeText.setVisible(false);

		// Screen 1
		participant_Name.setVisible(false);
		participant_Name_Label.setVisible(false);
		participant_Age.setVisible(false);
		participant_Age_Label.setVisible(false);
		for (int i = 0; i < 4; i++) participant_Gender[i].setVisible(false);
		participant_Gender_Label.setVisible(false);
		for (int i = 0; i < 4; i++) participant_Gender_Options_Labels[i].setVisible(false);
		for (int i = 0; i < 3; i++)	participant_HearingLoss[i].setVisible(false);
		participant_HearingLoss_Label.setVisible(false);
		for (int i = 0; i < 3; i++) participant_HearingLoss_Options_Labels[i].setVisible(false);
		for (int i = 0; i < 2; i++) participant_Handedness[i].setVisible(false);
		participant_Handedness_Label.setVisible(false);
		for (int i = 0; i < 2; i++) participant_Handedness_Options_Labels[i].setVisible(false);

		// Screen 2
		sessionDescription.setVisible(false);

		// Screen 3
		blockDescription.setVisible(false);
		blockTutorialLink.setVisible(false);

		// Screen 4
		task.setVisible(false);
		trainingMessage.setVisible(false);
		resetTarget.setVisible(false);
		targetFound.setVisible(false);

		// Screen 5
		testingMessage.setVisible(false);
		timeRemaining.setVisible(false);

		// Screen 6
		pleasantnessLabel.setVisible(false);
		pleasantness.setVisible(false);
		longevityLabel.setVisible(false);
		longevity.setVisible(false);

		// Screen 7
		thankYou.setVisible(false);

		// Screen 8
		countIn.setVisible(false);
	};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderSonificationFinalAudioProcessorEditor)
};
