#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<int> ParseStringToInts(string& inputString, string delimiter)
{
	vector<int> results;

	auto start = 0U;
	auto end = inputString.find(delimiter);
	while (end != string::npos)
	{
		if (!inputString.substr(start, end - start).empty())
		{
			results.push_back(stoi(inputString.substr(start, end - start)));
		}
		start = end + delimiter.length();
		end = inputString.find(delimiter, start);
	}
	results.push_back(stoi(inputString.substr(start, end)));

	return results;
}

int main()
{
	string inputLine;
	ifstream inputFile("input.txt");

	vector<int> initialTimers;
	vector<unsigned long long> timersCount(9);

	getline(inputFile, inputLine);

	if (!inputLine.empty())
	{
		initialTimers = ParseStringToInts(inputLine, ",");
	}

	for (const int timer : initialTimers)
	{
		timersCount[timer] += 1;
	}

	unsigned long long zeroTimerCount = 0;
	unsigned long long firstLanternfishesCount = 0;
	unsigned long long secondLanternfishesCount = 0;

	for (int dayCount = 1; dayCount <= 256; dayCount++)
	{
		zeroTimerCount = timersCount[0];
		for (int timer = 1; timer <= 8; timer++)
		{
			timersCount[timer - 1] = timersCount[timer];
		}

		timersCount[8] = zeroTimerCount;
		timersCount[6] += zeroTimerCount;

		if (dayCount == 80)
		{
			for (const unsigned long long& timerCount : timersCount)
			{
				firstLanternfishesCount += timerCount;
			}
		}
	}

	for (const unsigned long long& timerCount : timersCount)
	{
		secondLanternfishesCount += timerCount;
	}

	cout << "Part 1 - After 80 days, there are " << firstLanternfishesCount << " lanternfishes." << endl;
	cout << "Part 2 - After 256 days, there are " << secondLanternfishesCount << " lanternfishes." << endl;

	return 0;
}