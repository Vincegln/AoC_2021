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


int Factorial(int initialNumber)
{
	int result = 0;

	for (int i = 1; i <= initialNumber; i++)
	{
		result += i;
	}

	return result;
}

int ComputeFuelConsumption(vector<int>& initialPositions, int targetPosition, bool factorialCost = false)
{
	int fuelConsumption = 0;

	for (const int& i : initialPositions)
	{
		if (factorialCost)
		{
			fuelConsumption += Factorial(abs(i - targetPosition));
		}
		else
		{
			fuelConsumption += abs(i - targetPosition);
		}
	}

	return fuelConsumption;
}

void ComputePart1(vector<int>& initialPositions)
{
	int minFuelConsumption = INT_MAX;
	int lastComputedPosition = -1;

	for (unsigned int i = 0; i < initialPositions.size(); i++)
	{
		if (initialPositions[i] != lastComputedPosition)
		{
			lastComputedPosition = initialPositions[i];
			int currentConsumption = ComputeFuelConsumption(initialPositions, lastComputedPosition);

			if (currentConsumption < minFuelConsumption)
			{
				minFuelConsumption = currentConsumption;
			}
		}
	}

	cout << "Part 1 - The minimal fuel consumption is : " << minFuelConsumption << endl;
}

void ComputePart2(vector<int>& initialPositions)
{
	int minFuelConsumption = INT_MAX;
	int lastComputedPosition = -1;

	for (unsigned int i = 0; i < initialPositions.size(); i++)
	{
		if (initialPositions[i] != lastComputedPosition)
		{
			lastComputedPosition = initialPositions[i];
			int currentConsumption = ComputeFuelConsumption(initialPositions, lastComputedPosition, true);

			if (currentConsumption < minFuelConsumption)
			{
				minFuelConsumption = currentConsumption;
			}
		}
	}

	cout << "Part 2 - The minimal fuel consumption is : " << minFuelConsumption << endl;
}

int main()
{
	string inputLine;
	ifstream inputFile("input.txt");

	vector<int> initialPositions;

	getline(inputFile, inputLine);

	if (!inputLine.empty())
	{
		initialPositions = ParseStringToInts(inputLine, ",");
	}

	sort(initialPositions.begin(), initialPositions.end());

	ComputePart1(initialPositions);

	ComputePart2(initialPositions);

	return 0;
}