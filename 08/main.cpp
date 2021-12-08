#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

string ExtractCharactersInStrings(const string& firstString, const string& secondString, bool bSameCharacters)
{
	bool characterFound = false;

	string result = "";

	for (const auto& firstCharacter : firstString)
	{
		for (const auto& secondCharacter : secondString)
		{
			if (secondCharacter == firstCharacter)
			{
				characterFound = true;
				break;
			}
		}

		if ((characterFound && bSameCharacters) || (!characterFound && !bSameCharacters))
		{
			if (find(result.begin(), result.end(), firstCharacter) == result.end())
			{
				result.push_back(firstCharacter);
			}
		}
		characterFound = false;
	}

	for (const auto& firstCharacter : secondString)
	{
		for (const auto& secondCharacter : firstString)
		{
			if (secondCharacter == firstCharacter)
			{
				characterFound = true;
				break;
			}
		}

		if ((characterFound && bSameCharacters) || (!characterFound && !bSameCharacters))
		{
			if (find(result.begin(), result.end(), firstCharacter) == result.end())
			{
				result.push_back(firstCharacter);
			}
		}
		characterFound = false;
	}

	return result;
}

string CombineStringsUniqueCharacters(const string& firstString, const string& secondString)
{
	string longestString = firstString.length() > secondString.length() ? firstString : secondString;
	string smallestString = firstString.length() < secondString.length() ? firstString : secondString;
	bool characterFound = false;

	string result = longestString;

	for (const auto& firstCharacter : smallestString)
	{
		for (const auto& secondCharacter : longestString)
		{
			if (secondCharacter == firstCharacter)
			{
				characterFound = true;
				break;
			}
		}

		if (!characterFound)
		{
			result.push_back(firstCharacter);
		}
		characterFound = false;
	}

	return result;
}

int DigitsToInt(const vector<int>& digits)
{
	int result = 0;

	for (unsigned int i = 0; i < digits.size(); i++)
	{
		result += (int)(digits[i] * pow(10, digits.size() - 1 - i));
	}

	return result;
}

int StringToDigit(vector<char>& currentSegmentsConfiguration, const string& codedValue)
{
	map<vector<int>, int> const digitSegments{
		{ { 0,1,2,4,5,6 }, 0 },
		{ { 2,5 }, 1 },
		{ { 0, 2, 3, 4, 6 }, 2 },
		{ { 0,2,3,5,6 }, 3 },
		{ { 1,2,3,5 }, 4 },
		{ { 0,1,3,5,6 }, 5 },
		{ { 0,1,3,4,5,6 }, 6 },
		{ { 0,2,5 }, 7 },
		{ { 0,1,2,3,4,5,6 }, 8 },
		{ { 0,1,2,3,5,6 }, 9 }
	};

	vector<int> segment;

	for (const char& value : codedValue)
	{
		vector<char>::iterator it = find(currentSegmentsConfiguration.begin(), currentSegmentsConfiguration.end(), value);
		segment.push_back(it - currentSegmentsConfiguration.begin());
	}

	std::sort(segment.begin(), segment.end());

	int t = digitSegments.find(segment)->second;

	return t;
}

/*
	Segment order :

		0
	1		2
		3
	4		5
		6
*/

int main()
{
	string inputLine;
	ifstream inputFile("input.txt");

	unsigned int uniqueNbrSegments = 0;
	string delimiter = (" | ");

	unsigned long long sumOutputs = 0;
	int lineCount = 0;

	while (getline(inputFile, inputLine))
	{
		if (!inputLine.empty())
		{
			lineCount++;

			vector<char> currentSegmentsConfiguration(7);
			vector<string> currentCombinations(10);
			vector<string> fives;
			vector<string> sixes;
			vector<int> digits(4, -1);

			string signalsInputs = inputLine.substr(0, inputLine.find(delimiter));
			string digitsOutput = inputLine.substr(inputLine.find(delimiter) + delimiter.length(), inputLine.length());

			stringstream signalsSubString(signalsInputs);
			istream_iterator<string> signalsBegin(signalsSubString);
			istream_iterator<string> signalsEnd;
			vector<string> signalsWords(signalsBegin, signalsEnd);

			stringstream digitsSubString(digitsOutput);
			istream_iterator<string> digitsBegin(digitsSubString);
			istream_iterator<string> digitsEnd;
			vector<string> digitsWords(digitsBegin, digitsEnd);

			for (unsigned int i = 0; i < digitsWords.size(); i++)
			{
				switch (digitsWords[i].length())
				{
				case 2:
					digits[i] = 1;
					uniqueNbrSegments++;
					break;
				case 3:
					digits[i] = 7;
					uniqueNbrSegments++;
					break;
				case 4:
					digits[i] = 4;
					uniqueNbrSegments++;
					break;
				case 7:
					digits[i] = 8;
					uniqueNbrSegments++;
					break;
				}
			}

			if (find(digits.begin(),digits.end(),-1) == digits.end())
			{
				sumOutputs += DigitsToInt(digits);
				continue;
			}

			for (const string& word : signalsWords)
			{
				switch (word.length())
				{
				case 2:
					currentCombinations[1] = word;
					break;
				case 3:
					currentCombinations[7] = word;
					break;
				case 4:
					currentCombinations[4] = word;
					break;
				case 5:
					fives.push_back(word);
					break;
				case 6:
					sixes.push_back(word);
					break;
				case 7:
					currentCombinations[8] = word;
					break;
				}
			}

			// Zeroth segment
			string segment = ExtractCharactersInStrings(currentCombinations[7], currentCombinations[1], false);

			if (!segment.empty() && segment.length() == 1)
			{
				currentSegmentsConfiguration[0] = segment[0];
			}
			else
			{
				cout << "wtf bro(0)" << endl;
			}

			// Third segment
			string commonFiveSegments = ExtractCharactersInStrings(fives[0], fives[1], true);
			commonFiveSegments = ExtractCharactersInStrings(commonFiveSegments, fives[2], true);
			segment = ExtractCharactersInStrings(currentCombinations[4], commonFiveSegments, true);
			
			if (!segment.empty() && segment.length() == 1)
			{
				currentSegmentsConfiguration[3] = segment[0];
			}
			else
			{
				cout << "wtf bro(3)" << endl;
			}

			// First segment
			segment = ExtractCharactersInStrings(currentCombinations[4], segment, false);
			segment = ExtractCharactersInStrings(currentCombinations[1], segment, false);

			if (!segment.empty() && segment.length() == 1)
			{
				currentSegmentsConfiguration[1] = segment[0];
			}
			else
			{
				cout << "wtf bro(1)" << endl;
			}

			// Fifth segment
			string commonSixesSegments = ExtractCharactersInStrings(sixes[0], sixes[1], true);
			commonSixesSegments = ExtractCharactersInStrings(commonSixesSegments, sixes[2], true);

			segment = ExtractCharactersInStrings(commonSixesSegments, commonFiveSegments, false);
			segment = ExtractCharactersInStrings(segment, string(1,currentSegmentsConfiguration[1]), false);
			segment = ExtractCharactersInStrings(segment, string(1,currentSegmentsConfiguration[3]), false);

			if (!segment.empty() && segment.length() == 1)
			{
				currentSegmentsConfiguration[5] = segment[0];
			}
			else
			{
				cout << "wtf bro(5)" << endl;
			}

			// Second segment
			segment = "";
			segment += currentSegmentsConfiguration[1];
			segment += currentSegmentsConfiguration[3];
			segment += currentSegmentsConfiguration[5];
			segment = ExtractCharactersInStrings(segment, currentCombinations[4], false);

			if (!segment.empty() && segment.length() == 1)
			{
				currentSegmentsConfiguration[2] = segment[0];
			}
			else
			{
				cout << "wtf bro(2)" << endl;
			}

			// Sixth segment
			segment = ExtractCharactersInStrings(commonFiveSegments, string(1, currentSegmentsConfiguration[0]), false);
			segment = ExtractCharactersInStrings(segment, string(1, currentSegmentsConfiguration[3]), false);

			if (!segment.empty() && segment.length() == 1)
			{
				currentSegmentsConfiguration[6] = segment[0];
			}
			else
			{
				cout << "wtf bro(6)" << endl;
			}

			// Fourth segment
			segment = "";
			segment += currentSegmentsConfiguration[0];
			segment += currentSegmentsConfiguration[1];
			segment += currentSegmentsConfiguration[2];
			segment += currentSegmentsConfiguration[3];
			segment += currentSegmentsConfiguration[5];
			segment += currentSegmentsConfiguration[6];

			segment = ExtractCharactersInStrings(segment, currentCombinations[8], false);

			if (!segment.empty() && segment.length() == 1)
			{
				currentSegmentsConfiguration[4] = segment[0];
			}
			else
			{
				cout << "wtf bro(4)" << endl;
			}


			


			//
			for (unsigned int i = 0; i < digitsWords.size(); i++)
			{
				switch (digitsWords[i].length())
				{
				case 5:
					digits[i] = StringToDigit(currentSegmentsConfiguration, digitsWords[i]);
					break;
				case 6:
					digits[i] = StringToDigit(currentSegmentsConfiguration, digitsWords[i]);
					break;
				}
			}

			sumOutputs += DigitsToInt(digits);
		}
	}

	cout << "Part 1 - There are " << uniqueNbrSegments << " instances of digits that use a unique number of segments." << endl;
	cout << "Part 2 - The sum of all the output values equals " << sumOutputs << "." << endl;

	return 0;
}