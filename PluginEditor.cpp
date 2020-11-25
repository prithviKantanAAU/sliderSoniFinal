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
}

void SliderSonificationFinalAudioProcessorEditor::timerCallback()
{
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
    
}
