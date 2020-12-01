#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ParticipantDetails
{
public:
	ParticipantDetails() {};
	~ParticipantDetails() {};

	String name = "";
	String age = "";
	String gender = "";
	String hearingLoss = "";
	String hand = "";

	bool checkIfEntered()
	{
		bool allGood =
			(
				name != "" &&
				age != "" &&
				gender != "" &&
				hearingLoss != "" &&
				hand != ""
			);
		return allGood;
	}
};
