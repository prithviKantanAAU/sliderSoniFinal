#pragma once
#include <ctime>
#include "../JuceLibraryCode/JuceHeader.h"
#include "windows.h"

class ExperimentLogStore
{
public:
	ExperimentLogStore()
	{
	};
	~ExperimentLogStore() {};

	Time currentDateTime;
	FILE *fileObj[4];
	File forRootDirectory;
	String filePath_EXPT = "";
	String filePath_EXPT_LOG = "";
	String filePath_TRAJ1 = "";
	String filePath_TRAJ2 = "";
	String filePath_TRAJ3 = "";
	String names_Sessions[3] = { "Session 1", "Session 2", "Session 3" };
	String names_Variables[5] = { "Error", "Time", "Overshoots", "Pleasantness Rating", "Longevity Rating" };

	std::string expt_formatSpecifier =
		"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\n";

	std::string format_traj_BlockHeader =
		"%s,%s,%s,%s, %s,%s,%s,%s, %s,%s,%s,%s, %s,%s,%s,%s,"
		"%s,%s,%s,%s, %s,%s,%s,%s, %s,%s,%s,%s, %s,%s,%s,%s,"
		"%s,%s,%s,%s, %s,%s,%s,%s, \n";

	void save_Expt_LogLine(String commaSeparatedData)
	{
		// FIND NUMBER OF DATA VALUES PRESENT
		int numDataValues = countFreq(",", commaSeparatedData.toStdString());
		String data[10];

		// SEPARATE INTO SUBSTRINGS
		for (int i = 0; i < numDataValues; i++)
		{
			data[i] = commaSeparatedData.upToFirstOccurrenceOf(",", false, true);
			commaSeparatedData = commaSeparatedData.fromFirstOccurrenceOf(",", false, true);
		}

		// WRITE INTO LOG
		fprintf(
			fileObj[0],
			expt_formatSpecifier.c_str(),
			data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9]
		);
	};

	void save_Traj_LogLine(short sessionIdx, String commaSeparatedData)
	{
		int numDataValues = 40;
		String data[40];

		// SEPARATE INTO SUBSTRINGS
		for (int i = 0; i < numDataValues; i++)
		{
			data[i] = commaSeparatedData.upToFirstOccurrenceOf(",", false, true);
			commaSeparatedData = commaSeparatedData.fromFirstOccurrenceOf(",", false, true);
		}

		// WRITE INTO LOG
		fprintf(
			fileObj[sessionIdx + 1],
			format_traj_BlockHeader.c_str(),
			data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9],
			data[10], data[11], data[12], data[13], data[14], data[15], data[16], data[17], data[18], data[19],
			data[20], data[21], data[22], data[23], data[24], data[25], data[26], data[27], data[28], data[29],
			data[30], data[31], data[32], data[33], data[34], data[35], data[36], data[37], data[38], data[39]
		);
	};

	int countFreq(std::string pat, std::string txt)
	{
		int M = pat.length();
		int N = txt.length();
		int res = 0;

		/* A loop to slide pat[] one by one */
		for (int i = 0; i <= N - M; i++)
		{
			/* For current index i, check for
			   pattern match */
			int j;
			for (j = 0; j < M; j++)
				if (txt[i + j] != pat[j])
					break;

			// if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
			if (j == M)
			{
				res++;
				j = 0;
			}
		}
		return res;
	}

	// Returns Current Time
	String getCurrentTime()
	{
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H-%M-%S", timeinfo);
		std::string str(buffer);

		return String(str);
	}

	float minMax(float Value[4][10][3], float *minValue, float *maxValue)
	{

		*minValue = 0;
		*maxValue = 0;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					if (Value[i][j][k] < *minValue)
					{
						*minValue = Value[i][j][k];
					}

					if (Value[i][j][k] > *maxValue)
					{
						*maxValue = Value[i][j][k];
					}
				}
			}
		}
		return 0.0;
	}
};