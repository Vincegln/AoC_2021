#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>


using namespace std;

void ComputePart1()
{
	string inputLine;
	ifstream InputFile("input.txt");
	getline(InputFile, inputLine);

	int previousDepth = std::stoi(inputLine);
	int currentDepth = -1;
	int nbIncreases = 0;

	while (getline(InputFile, inputLine)) {
		currentDepth = std::stoi(inputLine);
		if (currentDepth > previousDepth)
		{
			nbIncreases++;
		}
		previousDepth = currentDepth;
	}

	cout << "Part 1 - Number of measurement increases : " << nbIncreases << endl;

	InputFile.close();
}

void ComputePart2()
{
	string inputLine;
	ifstream InputFile("input.txt");

	std::vector<int> measurements;
	int measurement = -1;

	while (getline(InputFile, inputLine)) {
		measurement = std::stoi(inputLine);
		if (measurement > 0)
		{
			measurements.push_back(measurement);
		}
	}

	InputFile.close();

	std::vector<int> window1;
	std::vector<int> window2;

	int window1Sum = -1;
	int window2Sum = -1;

	int nbIncreases = 0;

	for (unsigned int i = 0; i < measurements.size() - 3; i++)
	{
		window1.assign(measurements.cbegin() + i, measurements.cbegin() + i + 3);
		window2.assign(measurements.cbegin() + i + 1, measurements.cbegin() + i + 4);

		window1Sum = std::accumulate(window1.cbegin(), window1.cend(), decltype(window1)::value_type(0));
		window2Sum = std::accumulate(window2.cbegin(), window2.cend(), decltype(window2)::value_type(0));

		if (window2Sum > window1Sum)
		{
			nbIncreases++;
		}
	}

	cout << "Part 2 - Number of measurement increases : " << nbIncreases << endl;
}

int main()
{
	ComputePart1();
	ComputePart2();

	return 0;
}
