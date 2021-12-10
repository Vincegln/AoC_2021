#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>
#include <stack>

using namespace std;

unsigned long long ComputeAutocompleteScore(stack<char>& remainingSymbols)
{
	unsigned long long autocompleteScore = 0;

	while (!remainingSymbols.empty()) {
		char symbol = remainingSymbols.top();

		autocompleteScore *= 5;

		switch (symbol)
		{
		case '(':
			autocompleteScore += 1;
			break;
		case '[':
			autocompleteScore += 2;
			break;
		case '{':
			autocompleteScore += 3;
			break;
		case '<':
			autocompleteScore += 4;
			break;
		}

		remainingSymbols.pop();
	}

	return autocompleteScore;
}

int main()
{
	string inputLine;
	ifstream inputFile("input.txt");

	unsigned long long syntaxErrorScore = 0;
	vector<string> incompleteLines;
	vector<unsigned long long> autocompleteScores;

	while (getline(inputFile, inputLine))
	{
		if (!inputLine.empty())
		{
			stack<char> openingSymbols;
			bool errorFound = false;

			for (const char& inputChar : inputLine)
			{
				switch (inputChar)
				{
				case ')':
					if (openingSymbols.top() == '(')
					{
						openingSymbols.pop();
					}
					else
					{
						syntaxErrorScore += 3;
						errorFound = true;
					}
					break;
				case ']':
					if (openingSymbols.top() == '[')
					{
						openingSymbols.pop();
					}
					else
					{
						syntaxErrorScore += 57;
						errorFound = true;
					}
					break;
				case '}':
					if (openingSymbols.top() == '{')
					{
						openingSymbols.pop();
					}
					else
					{
						syntaxErrorScore += 1197;
						errorFound = true;
					}
					break;
				case '>':
					if (openingSymbols.top() == '<')
					{
						openingSymbols.pop();
					}
					else
					{
						syntaxErrorScore += 25137;
						errorFound = true;
					}
					break;
				default:
					openingSymbols.push(inputChar);
					break;
				}

				if (errorFound)
				{
					break;
				}
				
			}

			if (!errorFound)
			{
				incompleteLines.push_back(inputLine);
			}
		}
	}

	for (const string& incompleteLine : incompleteLines)
	{
		stack<char> openingSymbols;

		for (const char& inputChar : incompleteLine)
		{
			if (((inputChar == ')') && (openingSymbols.top() == '(')) || ((inputChar == '}') && (openingSymbols.top() == '{')) || ((inputChar == ']') && (openingSymbols.top() == '[')) || ((inputChar == '>') && (openingSymbols.top() == '<')))
			{
				openingSymbols.pop();
			}
			else if ((inputChar == '(') || (inputChar == '{') || (inputChar == '[') || (inputChar == '<'))
			{
				openingSymbols.push(inputChar);
			}
		}

		autocompleteScores.push_back(ComputeAutocompleteScore(openingSymbols));
	}

	sort(autocompleteScores.begin(), autocompleteScores.end());
	unsigned long long middleScore = autocompleteScores[(autocompleteScores.size() - 1) / 2];

	cout << "Part 1 - The total syntax error score is : " << syntaxErrorScore << "." << endl;
	cout << "Part 2 - The middle autocomplete score is : " << middleScore << "." << endl;

	return 0;
}