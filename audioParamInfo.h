#pragma once
#include <string>
#include "AudioParam_Single.h"

class audioParamInfo
{
public:

	AudioParam_Single audioParam_ObjectArray[10];
	short num_audioParams = 0;
	short activeAudioParam = 0;	

	audioParamInfo()
	{
		// 1
		audioParam_ObjectArray[0].set_nameTypeAddress("T_Pitch", 1, 1);
		audioParam_ObjectArray[0].initializeSoniParams(1, 0, 1, 0, 0, 100, 0);
		num_audioParams++;

		// 2
		audioParam_ObjectArray[1].set_nameTypeAddress("T_Tempo", 2, 1);
		audioParam_ObjectArray[1].initializeSoniParams(1, 0, 1, 0, 0, 100, 0);
		num_audioParams++;

		// 3
		audioParam_ObjectArray[2].set_nameTypeAddress("T_Synchronicity", 3, 1);
		audioParam_ObjectArray[2].initializeSoniParams(1, 0, 1, 0, 0, 100, 0);
		num_audioParams++;

		// 4
		audioParam_ObjectArray[3].set_nameTypeAddress("T_Harmonicity", 4, 1);
		audioParam_ObjectArray[3].initializeSoniParams(1, 0, 1, 0, 0, 100, 0);
		num_audioParams++;

		// 5
		audioParam_ObjectArray[4].set_nameTypeAddress("T_Brightness", 5, 1);
		audioParam_ObjectArray[4].initializeSoniParams(1, 0, 1, 0, 0, 100, 0);
		num_audioParams++;

		// 6
		audioParam_ObjectArray[5].set_nameTypeAddress("M_Pitch", 6, 2);
		audioParam_ObjectArray[5].initializeSoniParams(2, 0, 1, 0, 0, 100, 0);
		num_audioParams++;

		// 7
		audioParam_ObjectArray[6].set_nameTypeAddress("M_Tempo", 7, 2);
		audioParam_ObjectArray[6].initializeSoniParams(3, 0, 1, 0, 0, 100, 0);
		num_audioParams++;

		// 8
		audioParam_ObjectArray[7].set_nameTypeAddress("M_Synchronicity", 8, 1);
		audioParam_ObjectArray[7].initializeSoniParams(1, 0, 1, 0, 0, 100, 0);
		num_audioParams++;

		// 9
		audioParam_ObjectArray[8].set_nameTypeAddress("M_Harmonicity", 9, 1);
		audioParam_ObjectArray[8].initializeSoniParams(1, 0, 1, 0, 0, 100, 0);
		num_audioParams++;

		// 10
		audioParam_ObjectArray[9].set_nameTypeAddress("M_Brightness", 10, 1);
		audioParam_ObjectArray[9].initializeSoniParams(0.4, 0, 1, 0, 0, 100, 0);
		num_audioParams++;

	}

		

	~audioParamInfo() {};
};

