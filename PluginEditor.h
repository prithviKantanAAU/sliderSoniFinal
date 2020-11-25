#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "UIStrings.h"

class SliderSonificationFinalAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    SliderSonificationFinalAudioProcessorEditor (SliderSonificationFinalAudioProcessor&);
    ~SliderSonificationFinalAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    SliderSonificationFinalAudioProcessor& processor;
	void configureUI_Initial();
	void getNextScreenIdx();
	void toggleScreen(short newScreenIdx);
	void timerCallback();

	// Time Monitoring
	Label timeElapsed_Total;
	Label timeLeft_Task;

	// Experiment Monitoring
	Label session_Present;
	Label block_Present;
	Label trial_Present;

	// Data Collection
	Slider task;
	Slider pleasantness;
	Slider longevity;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderSonificationFinalAudioProcessorEditor)
};
