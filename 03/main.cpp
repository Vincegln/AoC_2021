#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <vector>


using namespace std;

vector<int> numberSearch(const vector<vector<int>>& vector2d, int bitIndex, bool mostCommonWanted)
{
	unsigned int onesCount = 0;
	unsigned int wantedBit = 0;

	for (unsigned int i = 0; i < vector2d.size(); i++)
	{
		if (vector2d[i][bitIndex] > 0)
		{
			onesCount++;
		}
	}

	if ((mostCommonWanted && (onesCount >= ((vector2d.size() + 1) / 2))) || (!mostCommonWanted && (onesCount < ((vector2d.size() + 1) / 2))))
	{
		wantedBit = 1;
	}

	vector<vector<int>> reducedVector2d;

	for (unsigned int i = 0; i < vector2d.size(); i++)
	{
		if (vector2d[i][bitIndex] == wantedBit)
		{
			reducedVector2d.push_back(vector2d[i]);
		}
	}

	if (reducedVector2d.size() > 1)
	{
		bitIndex++;
		return numberSearch(reducedVector2d, bitIndex, mostCommonWanted);
	}
	else if (reducedVector2d.size() == 1)
	{
		return reducedVector2d[0];
	}
	else
	{
		return vector<int>();
	}
}

int bitsToInt(const vector<int>& bits)
{
	int result = 0;

	for (unsigned int i = 0; i < bits.size(); i++)
	{
		if (bits[i] > 0)
		{
			result += (int)pow(2, bits.size() - 1 - i);
		}
	}

	return result;
}

void ComputePart1()
{
	string inputLine;
	ifstream inputFile("input.txt");

	getline(inputFile, inputLine);

	std::vector<int> measurements(inputLine.length());
	int bit = -1;
	int lineCount = 0;

	do {
		if (inputLine != "")
		{
			lineCount++;

			for (unsigned int i = 0; i < inputLine.length(); i++)
			{
				bit = inputLine[i] - '0';
				if (bit > 0)
				{
					measurements[i]++;
				}
			}
		}
	} while (getline(inputFile, inputLine));

	int gammaInt = 0;
	int epsilonInt = 0;

	for (unsigned int i = 0; i < measurements.size(); i++)
	{
		if (measurements[i] > (lineCount / 2))
		{
			gammaInt += (int)pow(2, measurements.size() - 1 - i);
		}
		else
		{
			epsilonInt += (int)pow(2, measurements.size() - 1 - i);
		}
	}

	cout << "Part 1 - The power consumption of the submarine is : " << gammaInt * epsilonInt << endl;

	inputFile.close();
}

void ComputePart2()
{
	string inputLine;
	ifstream inputFile("input.txt");

	vector<vector<int>> report;


	while (getline(inputFile, inputLine))
	{
		if (inputLine != "")
		{
			vector<int> reportInts;

			for (unsigned int i = 0; i < inputLine.length(); i++)
			{
				reportInts.push_back(inputLine[i] - '0');
			}

			report.push_back(reportInts);
		}
	}

	vector<int> oxygenGenBits = numberSearch(report, 0, true);
	vector<int> co2ScrubBits = numberSearch(report, 0, false);

	int oxygenGenRating = bitsToInt(oxygenGenBits);
	int co2ScrubRating = bitsToInt(co2ScrubBits);

	cout << "Part 2 - The life support rating of the submarine is : " << oxygenGenRating * co2ScrubRating << endl;
}

int main()
{
	ComputePart1();
	ComputePart2();

	return 0;
}