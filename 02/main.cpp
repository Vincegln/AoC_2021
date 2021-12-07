#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ComputePart1()
{
	string inputLine;
	ifstream inputFile("input.txt");

	int horizontalPos = 0;
	int depth = 0;

	string instruction = "";
	int instructionValue = 0;

	while (getline(inputFile, inputLine)) {
		if (inputLine != "")
		{
			instruction = inputLine.substr(0, inputLine.find(" "));
			instructionValue = std::stoi(inputLine.substr(inputLine.find(" ") + 1, inputLine.length()));

			if (instruction == "forward")
			{
				horizontalPos += instructionValue;
			}
			else if (instruction == "up")
			{
				depth -= instructionValue;
			}
			else if (instruction == "down")
			{
				depth += instructionValue;
			}
		}
	}

	inputFile.close();

	cout << "Part 1 - Final position : " << horizontalPos * depth << endl;
}

void ComputePart2()
{
	string inputLine;
	ifstream inputFile("input.txt");

	int horizontalPos = 0;
	int depth = 0;
	int aim = 0;

	string instruction = "";
	int instructionValue = 0;

	while (getline(inputFile, inputLine)) {
		if (inputLine != "")
		{
			instruction = inputLine.substr(0, inputLine.find(" "));
			instructionValue = std::stoi(inputLine.substr(inputLine.find(" ") + 1, inputLine.length()));

			if (instruction == "forward")
			{
				horizontalPos += instructionValue;
				depth += instructionValue * aim;
			}
			else if (instruction == "up")
			{
				aim -= instructionValue;
			}
			else if (instruction == "down")
			{
				aim += instructionValue;
			}
		}
	}

	inputFile.close();

	cout << "Part 2 - Final position : " << horizontalPos * depth << endl;
}

int main()
{
	ComputePart1();
	ComputePart2();

	return 0;
}