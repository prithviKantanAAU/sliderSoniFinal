#include "PluginProcessor.h"
#include "PluginEditor.h"

SliderSonificationFinalAudioProcessorEditor::SliderSonificationFinalAudioProcessorEditor (SliderSonificationFinalAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (1200, 400);
	startTimerHz(50);
	configureUI_Initial();
}

SliderSonificationFinalAudioProcessorEditor::~SliderSonificationFinalAudioProcessorEditor()
{
}

void SliderSonificationFinalAudioProcessorEditor::configureUI_Initial()
{
	// TESTING
	addAndMakeVisible(toggleScreenIdx);
	toggleScreenIdx.setRange(0, 7);
	toggleScreenIdx.setValue(0);
	toggleScreenIdx.setNumDecimalPlacesToDisplay(0);
	toggleScreenIdx.onValueChange = [this]
	{
		processor.experimentControl.idx_Screen = (int)toggleScreenIdx.getValue();
	};

	// EXPERIMENT LABELS
	addAndMakeVisible(timeElapsed_Total);
	addAndMakeVisible(session_Present);
	addAndMakeVisible(block_Present);
	addAndMakeVisible(trial_Present);

	// SCREEN 0
	addAndMakeVisible(welcomeText);
	welcomeText.setJustificationType(juce::Justification::centred);
	welcomeText.setText(uiStrings.welcomeText, dontSendNotification);
	welcomeText.setFont(juce::Font(24.0f, juce::Font::bold));
}

void SliderSonificationFinalAudioProcessorEditor::timerCallback()
{
	bool isScreenChanged = (processor.experimentControl.idx_Screen != screenIdx_z1);
	if (isScreenChanged) 	toggleScreen(processor.experimentControl.idx_Screen);

	updateExptLabels();

}

void SliderSonificationFinalAudioProcessorEditor::getNextScreenIdx()
{
}

void SliderSonificationFinalAudioProcessorEditor::toggleScreen(short newScreenIdx)
{
}

void SliderSonificationFinalAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void SliderSonificationFinalAudioProcessorEditor::resized()
{
	toggleScreenIdx.setBounds(10, 10, 200, 20);
	timeElapsed_Total.setBounds(1030, 10, 170, 20);
	session_Present.setBounds(1030, 30, 170, 20);
	block_Present.setBounds(1030, 50, 170, 20);
	trial_Present.setBounds(1030, 70, 170, 20);

	// SCREEN 0
	welcomeText.setBounds(0, 160, 1200, 80);
}
