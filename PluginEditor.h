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
			String(processor.experimentControl.session_Completed + 1)
			,dontSendNotification
		);

		block_Present.setText
		(
			uiStrings.block_Current +
			String(processor.experimentControl.block_Completed + 1)
			,dontSendNotification
		);

		trial_Present.setText
		(
			uiStrings.trial_Current +
			String(processor.experimentControl.trial_Current + 1),
			dontSendNotification
		);
	}

	// Permanently Visible Elements
	// Testing
	Slider toggleScreenIdx;
	int screenIdx_z1 = 0;

	// Time Monitoring
	Label timeElapsed_Total;
	Label timeLeft_Task;

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

	// Screen 2

	// Screen 3

	// Screen 4

	// Screen 5

	// Screen 6

	// Screen 7

	// Data Collection
	Slider task;

	// Data Collection
	Slider pleasantness;
	Slider longevity;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderSonificationFinalAudioProcessorEditor)
};