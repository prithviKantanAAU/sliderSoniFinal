#include "PluginProcessor.h"
#include "PluginEditor.h"

SliderSonificationFinalAudioProcessorEditor::SliderSonificationFinalAudioProcessorEditor (SliderSonificationFinalAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), exptProgress(exptProgress_Var)
{
    setSize (1200, 400);
	startTimerHz(50);
	configureUI_Initial();
	toggleScreen(processor.experimentControl.idx_Screen);
}

SliderSonificationFinalAudioProcessorEditor::~SliderSonificationFinalAudioProcessorEditor()
{
}

void SliderSonificationFinalAudioProcessorEditor::configureUI_Initial()
{
	addAndMakeVisible(screenHeader);
	screenHeader.setText(uiStrings.screenHeaders[processor.experimentControl.idx_Screen],dontSendNotification);
	screenHeader.setJustificationType(juce::Justification::centred);
	screenHeader.setFont(juce::Font(30.0f, juce::Font::bold));
	
	addAndMakeVisible(warning);
	warning.setJustificationType(juce::Justification::centred);
	warning.setColour(warning.textColourId, Colours::red);
	warning.setFont(juce::Font(16.0f, juce::Font::italic));

	addAndMakeVisible(exptProgress);
	exptProgress.setColour(exptProgress.foregroundColourId, Colours::white);

	// TESTING
	addAndMakeVisible(toggleScreenIdx);
	toggleScreenIdx.setSliderStyle(Slider::IncDecButtons);
	toggleScreenIdx.setRange(0, 7, 1);
	toggleScreenIdx.setValue(0);
	toggleScreenIdx.setNumDecimalPlacesToDisplay(0);
	toggleScreenIdx.onValueChange = [this]
	{
		processor.experimentControl.idx_Screen = (int) toggleScreenIdx.getValue();
		/*processor.experimentControl.saveLog_EXPT();
		processor.experimentControl.saveLog_TRAJ();*/
	};

	// EXPERIMENT LABELS
	addAndMakeVisible(timeElapsed_Total);
	addAndMakeVisible(session_Present);
	addAndMakeVisible(block_Present);
	addAndMakeVisible(trial_Present);
	addAndMakeVisible(continuePrompt);

	// SCREEN 0
	addAndMakeVisible(welcomeText);
	welcomeText.setJustificationType(juce::Justification::centred);
	welcomeText.setText(uiStrings.welcomeText, dontSendNotification);
	welcomeText.setFont(juce::Font(24.0f, juce::Font::bold));

	continuePrompt.setJustificationType(juce::Justification::centred);
	updateContinuePrompt(processor.experimentControl.idx_Screen);
	continuePrompt.setFont(juce::Font(24.0f, juce::Font::bold));
	continuePrompt.setColour(continuePrompt.textColourId, Colours::yellow);

	// SCREEN 1
	addAndMakeVisible(participant_Name);
	addAndMakeVisible(participant_Name_Label);
	participant_Name_Label.setText(uiStrings.participant_Name, dontSendNotification);
	participant_Name_Label.attachToComponent(&participant_Name, true);
	participant_Name.setJustification(Justification::centred);
	participant_Name.onTextChange = [this]
	{
		String name = participant_Name.getText();
		processor.experimentControl.participantDetails.name = name;
	};

	addAndMakeVisible(participant_Age);
	addAndMakeVisible(participant_Age_Label);
	participant_Age_Label.setText(uiStrings.participant_Age, dontSendNotification);
	participant_Age_Label.attachToComponent(&participant_Age, true);
	participant_Age.setJustification(Justification::centred);
	participant_Age.onTextChange = [this]
	{
		String age = participant_Age.getText();
		processor.experimentControl.participantDetails.age = age;
	};

	addAndMakeVisible(participant_Gender_Label);
	participant_Gender_Label.setText(uiStrings.participant_Gender, dontSendNotification);
	for (int i = 0; i < 4; i++)
	{
		addAndMakeVisible(participant_Gender[i]);
		addAndMakeVisible(participant_Gender_Options_Labels[i]);
		participant_Gender_Options_Labels[i].attachToComponent(&participant_Gender[i], true);
		participant_Gender_Options_Labels[i].setText(uiStrings.participant_Gender_Options[i],dontSendNotification);

		participant_Gender[i].onClick = [this,i]
		{
			if (participant_Gender[i].getToggleState())
			{
				for (int j = 0; j < 4; j++)
				{
					if (j != i) participant_Gender[j].setToggleState(false, dontSendNotification);
				}
				processor.experimentControl.participantDetails.gender = uiStrings.participant_Gender_Options[i];
			}
			else processor.experimentControl.participantDetails.gender = "";
		};
	}
	
	addAndMakeVisible(participant_HearingLoss_Label);
	participant_HearingLoss_Label.setText(uiStrings.participant_HearingLoss, dontSendNotification);
	for (int i = 0; i < 3; i++)
	{
		addAndMakeVisible(participant_HearingLoss[i]);
		addAndMakeVisible(participant_HearingLoss_Options_Labels[i]);
		participant_HearingLoss_Options_Labels[i].attachToComponent(&participant_HearingLoss[i], true);
		participant_HearingLoss_Options_Labels[i].setText(uiStrings.participant_HearingLoss_Options[i], dontSendNotification);

		participant_HearingLoss[i].onClick = [this,i]
		{
			if (participant_HearingLoss[i].getToggleState())
			{
				for (int j = 0; j < 3; j++)
				{
					if (j != i) participant_HearingLoss[j].setToggleState(false, dontSendNotification);
				}
				processor.experimentControl.participantDetails.hearingLoss = uiStrings.participant_HearingLoss_Options[i];
			}
			else processor.experimentControl.participantDetails.hearingLoss = "";
		};
	}
	
	addAndMakeVisible(participant_Handedness_Label);
	participant_Handedness_Label.setText(uiStrings.participant_Handedness, dontSendNotification);
	for (int i = 0; i < 2; i++)
	{
		addAndMakeVisible(participant_Handedness[i]);
		addAndMakeVisible(participant_Handedness_Options_Labels[i]);
		participant_Handedness_Options_Labels[i].attachToComponent(&participant_Handedness[i], true);
		participant_Handedness_Options_Labels[i].setText(uiStrings.participant_Handedness_Options[i], dontSendNotification);

		participant_Handedness[i].onClick = [this,i]
		{
			if (participant_Handedness[i].getToggleState())
			{
				for (int j = 0; j < 2; j++)
				{
					if (j != i) participant_Handedness[j].setToggleState(false, dontSendNotification);
				}
				processor.experimentControl.participantDetails.hand = uiStrings.participant_Handedness_Options[i];
			}
			else processor.experimentControl.participantDetails.hand = "";
		};
	}

	// SCREEN 2
	addAndMakeVisible(sessionDescription);
	sessionDescription.setText(
		uiStrings.session_Instructions[processor.experimentControl.session_CurrentIdx]
		, dontSendNotification
	);
	sessionDescription.setJustificationType(juce::Justification::centred);
	sessionDescription.setFont(juce::Font(24.0f, juce::Font::bold));
	
	// SCREEN 3
	addAndMakeVisible(blockDescription);
	blockDescription.setText(
		uiStrings.block_Names[processor.experimentControl.block_CurrentIdx]
		, dontSendNotification
	);
	blockDescription.setJustificationType(juce::Justification::centred);
	blockDescription.setFont(juce::Font(24.0f, juce::Font::bold));
	addAndMakeVisible(blockTutorialLink);
	blockTutorialLink.setButtonText("Watch Tutorial");
	blockTutorialLink.setJustificationType(juce::Justification::centred);
	blockTutorialLink.setURL(uiStrings.block_tutorial_URLs[processor.experimentControl.block_CurrentIdx]);

	// SCREEN 4
	addAndMakeVisible(task);
	task.setRange(0, 1);
	task.setValue(0.000001);
	task.setTextBoxStyle(Slider::NoTextBox, true, 10, 10);
	task.setColour(task.trackColourId, Colours::yellow);
	task.setColour(task.backgroundColourId, Colours::white);
	task.setColour(task.thumbColourId, Colours::blue);
	task.onValueChange = [this]
	{
		processor.experimentControl.val_taskSlider = task.getValue();
		processor.experimentControl.mapTargetDistance();
		// DO FAUST SEQUENCER MAPPING TOO
	};

	addAndMakeVisible(resetTarget);
	resetTarget.setButtonText("New Target");
	resetTarget.setColour(resetTarget.buttonColourId, Colours::red);
	resetTarget.onClick = [this]
	{
		task.setValue(0);
		processor.experimentControl.getNewTargetValue();
	};

	addAndMakeVisible(trainingMessage);
	trainingMessage.setJustificationType(juce::Justification::centred);
	trainingMessage.setFont(juce::Font(24.0f, juce::Font::bold));
	trainingMessage.setText(uiStrings.isTraining, dontSendNotification);

	addAndMakeVisible(targetFound);
	targetFound.setText("TARGET FOUND",dontSendNotification);
	targetFound.setJustificationType(juce::Justification::centred);
	targetFound.setFont(juce::Font(24.0f, juce::Font::bold));
	targetFound.setColour(targetFound.textColourId, Colours::green);

	// SCREEN 5
	addAndMakeVisible(testingMessage);
	testingMessage.setJustificationType(juce::Justification::centred);
	testingMessage.setFont(juce::Font(24.0f, juce::Font::bold));
	trial_Present.setFont(juce::Font(16.0f, juce::Font::bold));

	addAndMakeVisible(timeRemaining);
	timeRemaining.setJustificationType(juce::Justification::centred);
	timeRemaining.setFont(juce::Font(24.0f, juce::Font::bold));
	timeRemaining.setText(
	"Remaining Time: " + String((int)processor.experimentControl.timeRemaining + 0.9) + "sec"
	, dontSendNotification
	);

	// SCREEN 6
	addAndMakeVisible(pleasantness);
	addAndMakeVisible(pleasantnessLabel);
	pleasantness.setRange(1, 7, 1);
	pleasantness.setValue(4);
	pleasantness.setNumDecimalPlacesToDisplay(0);
	pleasantness.setColour(pleasantness.textBoxBackgroundColourId, Colours::yellow);
	pleasantness.setColour(pleasantness.textBoxTextColourId, Colours::black);
	pleasantness.setSliderStyle(Slider::IncDecButtons);
	pleasantnessLabel.setText(uiStrings.pleasantnessText, dontSendNotification);
	pleasantnessLabel.setJustificationType(juce::Justification::centred);
	pleasantnessLabel.setFont(juce::Font(24.0f, juce::Font::bold));
	pleasantness.onValueChange = [this]
	{
		processor.experimentControl.rating_pleasantness_presentTrial = (int)pleasantness.getValue();
	};

	addAndMakeVisible(longevity);
	addAndMakeVisible(longevityLabel);
	longevity.setRange(1, 7, 1);
	longevity.setValue(4);
	longevity.setNumDecimalPlacesToDisplay(0);
	longevity.setColour(longevity.textBoxBackgroundColourId, Colours::yellow);
	longevity.setColour(longevity.textBoxTextColourId, Colours::black);
	longevity.setSliderStyle(Slider::IncDecButtons);
	longevityLabel.setText(uiStrings.longevityText, dontSendNotification);
	longevityLabel.setJustificationType(juce::Justification::centred);
	longevityLabel.setFont(juce::Font(24.0f, juce::Font::bold));
	longevity.onValueChange = [this]
	{
		processor.experimentControl.rating_longevity_presentTrial = (int)longevity.getValue();
	};

	// SCREEN 7
	addAndMakeVisible(thankYou);
	thankYou.setJustificationType(juce::Justification::centred);
	thankYou.setText(uiStrings.thankYou, dontSendNotification);
	thankYou.setFont(juce::Font(24.0f, juce::Font::bold));

	// SCREEN 8
	addAndMakeVisible(countIn);
	countIn.setJustificationType(juce::Justification::centred);
	countIn.setFont(juce::Font(24.0f, juce::Font::bold));
}

void SliderSonificationFinalAudioProcessorEditor::timerCallback()
{
	bool isScreenChanged = (processor.experimentControl.idx_Screen != screenIdx_z1);
	bool isTrialChanged = (processor.experimentControl.trial_Current != trialIdx_z1);
	if (isScreenChanged) 	toggleScreen(processor.experimentControl.idx_Screen);
	if (isTrialChanged)		task.setValue(0);
	warning.setText(uiStrings.warnings[processor.experimentControl.idx_Screen], dontSendNotification);
	warning.setVisible(!processor.isAllOK);
	updateExptLabels();
	updateTimeRemaining();
	screenIdx_z1 = processor.experimentControl.idx_Screen;
	trialIdx_z1 = processor.experimentControl.trial_Current;
}

void SliderSonificationFinalAudioProcessorEditor::getNextScreenIdx()
{
}

void SliderSonificationFinalAudioProcessorEditor::toggleScreen(short newScreenIdx)
{
	hideScreenSpecificUI();
	updateContinuePrompt(newScreenIdx);
	screenHeader.setText(uiStrings.screenHeaders[processor.experimentControl.idx_Screen], dontSendNotification);

	switch (newScreenIdx)
	{
	case 0:											// Welcome Screen
		welcomeText.setVisible(true);
		break;
	case 1:											// Personal Details Screen
		participant_Name.setVisible(true);
		participant_Name_Label.setVisible(true);
		participant_Age.setVisible(true);
		participant_Age_Label.setVisible(true);
		for (int i = 0; i < 4; i++) participant_Gender[i].setVisible(true);
		participant_Gender_Label.setVisible(true);
		for (int i = 0; i < 4; i++) participant_Gender_Options_Labels[i].setVisible(true);
		for (int i = 0; i < 3; i++)	participant_HearingLoss[i].setVisible(true);
		participant_HearingLoss_Label.setVisible(true);
		for (int i = 0; i < 3; i++) participant_HearingLoss_Options_Labels[i].setVisible(true);
		for (int i = 0; i < 2; i++) participant_Handedness[i].setVisible(true);
		participant_Handedness_Label.setVisible(true);
		for (int i = 0; i < 2; i++) participant_Handedness_Options_Labels[i].setVisible(true);
		break;
	case 2:											// Session Intro Screen
		sessionDescription.setText(
			uiStrings.session_Instructions[processor.experimentControl.session_CurrentIdx]
			,dontSendNotification
		);
		sessionDescription.setVisible(true);
		break;
	case 3:											// Block Intro/Instruction Screen
		blockDescription.setText(
			uiStrings.block_Names[processor.experimentControl.block_CurrentIdx]
			, dontSendNotification
		);
		updateTutorialURL(processor.experimentControl.block_CurrentIdx);
		blockDescription.setVisible(true);
		blockTutorialLink.setVisible(true);
		break;
	case 4:											// Training Screen
		task.setVisible(true);
		trainingMessage.setVisible(true);
		resetTarget.setVisible(true);
		task.setValue(0);
		break;
	case 5:											// Trial Screen
		timeRemaining.setVisible(true);
		testingMessage.setText(uiStrings.session_Instructions[processor.experimentControl.session_CurrentIdx]
		, dontSendNotification);
		testingMessage.setVisible(true);
		task.setVisible(true);
		task.setValue(0);
		break;
	case 6:											// Subjective Data Screen
		pleasantness.setValue(4);
		longevity.setValue(4);
		pleasantnessLabel.setVisible(true);
		pleasantness.setVisible(true);
		longevity.setVisible(true);
		longevityLabel.setVisible(true);
		break;
	case 7:											// Conclusion Screen
		thankYou.setVisible(true);
		break;
	case 8:
		countIn.setVisible(true);
		break;
	}
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
	screenHeader.setBounds(0, 0, 1200, 45);
	warning.setBounds(0, 330, 1200, 25);

	//toggleScreenIdx.setBounds(10, 10, 200, 20);
	timeElapsed_Total.setBounds(1030, 10, 170, 20);
	session_Present.setBounds(1030, 30, 170, 20);
	block_Present.setBounds(1030, 50, 170, 20);
	trial_Present.setBounds(1030, 70, 170, 20);
	continuePrompt.setBounds(0, 330, 1200, 80);
	exptProgress.setBounds(0, 385, 1200, 15);

	// SCREEN 0
	welcomeText.setBounds(0, 160, 1200, 80);

	// SCREEN 1
	participant_Name.setBounds(80,50,400,30);
	participant_Age.setBounds(80,90,80,30);
	participant_Gender_Label.setBounds(80,130,400,30);
	for (int i = 0; i < 4; i++) participant_Gender[i].setBounds(80 + 150*i,160,150,30);
	participant_HearingLoss_Label.setBounds(80, 200, 400, 30);
	for (int i = 0; i < 3; i++)	participant_HearingLoss[i].setBounds(80 + 150 * i, 230, 150, 30);
	participant_Handedness_Label.setBounds(80, 270, 400, 30);
	for (int i = 0; i < 2; i++) participant_Handedness[i].setBounds(80 + 150 * i, 300, 150, 30);

	// SCREEN 2
	sessionDescription.setBounds(0, 160, 1200, 80);

	// SCREEN 3
	blockDescription.setBounds(0, 160, 1200, 80);
	blockTutorialLink.setBounds(0, 250, 1200, 30);

	// SCREEN 4
	trainingMessage.setBounds(0, 140, 1200, 40);
	task.setBounds(10, 200, 1180, 30);
	targetFound.setBounds(400, 230, 400, 30);
	resetTarget.setBounds(1040, 230, 140, 25);

	// SCREEN 5
	testingMessage.setBounds(0, 140, 1200, 30);
	timeRemaining.setBounds(0, 60, 1200, 80);

	// SCREEN 6
	pleasantnessLabel.setBounds(0, 100, 1200, 50);
	pleasantness.setBounds(400, 150, 400, 30);
	longevityLabel.setBounds(0, 250, 1200, 50);
	longevity.setBounds(400, 300, 400, 30);

	// SCREEN 7
	thankYou.setBounds(0, 160, 1200, 80);

	// SCREEN 8
	countIn.setBounds(0, 160, 1200, 80);
}
