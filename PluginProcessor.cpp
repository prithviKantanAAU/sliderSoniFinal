#include "PluginProcessor.h"
#include "PluginEditor.h"

SliderSonificationFinalAudioProcessor::SliderSonificationFinalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	startTimer(1);
}

SliderSonificationFinalAudioProcessor::~SliderSonificationFinalAudioProcessor()
{
	stopTimer();
}

void SliderSonificationFinalAudioProcessor::hiResTimerCallback()
{
	experimentControl.updateTimeVariables(0.001);
	experimentControl.decrementTimeRemaining(0.001);					// ONLY HAPPENS IN SESSION 1

	// CHECK FOR SPACE KEY PRESSES
	isSpaceDown = spaceBarContinue.isKeyCurrentlyDown(KeyPress::spaceKey);
	if (isSpaceDown && !wasSpaceDown) handleProceed();
	if (experimentControl.timeRemaining <= 0.000001 && experimentControl.isTrialON) handleProceed();
	wasSpaceDown = isSpaceDown;
}

void SliderSonificationFinalAudioProcessor::handleProceed()
{
	int scr = experimentControl.idx_Screen;
	int sess = experimentControl.session_Completed;
	int blk = experimentControl.block_Completed;
	int trial = experimentControl.trial_Current;

	switch (scr)
	{
	case 0:				// WELCOME SCREEN
		isAllOK = true;
		if (isAllOK) experimentControl.idx_Screen = 1;
		break;
	case 1:				// PARTICIPANT DETAILS SCREEN
		isAllOK = participantDetails.checkIfEntered(); 
		if (isAllOK) experimentControl.idx_Screen = 2;
		break;
	case 2:				// SESSION INTRO SCREEN
		isAllOK = true;
 		if (isAllOK) experimentControl.idx_Screen = 3;
		break;
	case 3:				// BLOCK INTRO SCREEN
		if (isAllOK) experimentControl.idx_Screen = 4;
		break;
	case 4:				// TRAINING SCREEN
		isAllOK = true;
		if (isAllOK)
		{
			experimentControl.idx_Screen = 5;
			experimentControl.beginTrial();
		}
		break;
	case 5:				// TESTING SCREEN
		experimentControl.endTrial();
		break;
	case 6:				// SUBJECTIVE RATINGS SCREEN
		experimentControl.endBlock();
		break;
	case 7:				// CONCLUSION
		break;
	}
};

const String SliderSonificationFinalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SliderSonificationFinalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SliderSonificationFinalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SliderSonificationFinalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SliderSonificationFinalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SliderSonificationFinalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SliderSonificationFinalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SliderSonificationFinalAudioProcessor::setCurrentProgram (int index)
{
}

const String SliderSonificationFinalAudioProcessor::getProgramName (int index)
{
    return {};
}

void SliderSonificationFinalAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SliderSonificationFinalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SliderSonificationFinalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SliderSonificationFinalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SliderSonificationFinalAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool SliderSonificationFinalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SliderSonificationFinalAudioProcessor::createEditor()
{
    return new SliderSonificationFinalAudioProcessorEditor (*this);
}

//==============================================================================
void SliderSonificationFinalAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SliderSonificationFinalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SliderSonificationFinalAudioProcessor();
}
