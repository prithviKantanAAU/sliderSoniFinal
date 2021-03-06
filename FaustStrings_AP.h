#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class FaustStrings_AP
{
public:
	FaustStrings_AP()
	{
	};
	~FaustStrings_AP() {};

	String baseName = "/SliderSoniFinal/";

	String tradSoniToggle =
		baseName + "Traditional";

	String tradSoniChoice = baseName + 
		"Mapping_Tabs/Sonification_Types/Traditional_Strategies/Choice_Traditional";

	String SonificationNames[20] =
	{
		"Mapping_Tabs/Sonification_Types/AP_Values/Soni_1",			// T - Pitch
		"Mapping_Tabs/Sonification_Types/AP_Values/Soni_2",			// T - Tempo
		"Mapping_Tabs/Sonification_Types/AP_Values/Soni_3",			// T - Synchronicity
		"Mapping_Tabs/Sonification_Types/AP_Values/Soni_4",			// T - Harmonicity
		"Mapping_Tabs/Sonification_Types/AP_Values/Soni_5",			// T - Brightness
		"Mapping_Tabs/Sonification_Types/AP_Values/Soni_6",			// M - Pitch (Degree)
		"Mapping_Tabs/Sonification_Types/AP_Values/Soni_7",			// M - Tempo
		"Mapping_Tabs/Sonification_Types/AP_Values/Soni_8",			// M - Synchronicity
		"Mapping_Tabs/Sonification_Types/AP_Values/Soni_9",			// M - Harmonicity
		"Mapping_Tabs/Sonification_Types/AP_Values/Soni_10",			// M - Brightness
	};
};



