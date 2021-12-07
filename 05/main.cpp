#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
    string inputLine;
    ifstream inputFile("input.txt");

    map<pair<int, int>, int> dotGridPart1;
    map<pair<int, int>, int> dotGridPart2;
    string dotsDelimiter = " -> ";
    string coordinatesDelimiter = ",";
    int diff = -1;
    int smallerCoord = -1;

    while (getline(inputFile, inputLine))
    {
        if (!inputLine.empty())
        {
            string firstCoordString = inputLine.substr(0, inputLine.find(dotsDelimiter));
            string secondCoordString = inputLine.substr(inputLine.find(dotsDelimiter) + dotsDelimiter.length());

            string one = firstCoordString.substr(0, firstCoordString.find(coordinatesDelimiter));
            string two = firstCoordString.substr(firstCoordString.find(coordinatesDelimiter) + coordinatesDelimiter.length());
            string three = secondCoordString.substr(0, secondCoordString.find(coordinatesDelimiter));
            string four = secondCoordString.substr(secondCoordString.find(coordinatesDelimiter) + coordinatesDelimiter.length());

            pair<int, int> firstCoord = make_pair(stoi(one), stoi(two));
            pair<int, int> secondCoord = make_pair(stoi(three), stoi(four));

            if (firstCoord.first == secondCoord.first)
            {
                diff = abs(firstCoord.second - secondCoord.second);
                smallerCoord = min(firstCoord.second, secondCoord.second);

				for (int i = 0; i <= diff; i++)
				{
					dotGridPart1[make_pair(firstCoord.first, smallerCoord + i)] += 1;
                    dotGridPart2[make_pair(firstCoord.first, smallerCoord + i)] += 1;
				}
            }
            else if (firstCoord.second == secondCoord.second)
            {
				diff = abs(firstCoord.first - secondCoord.first);
                smallerCoord = min(firstCoord.first, secondCoord.first);

				for (int i = 0; i <= diff; i++)
				{
					dotGridPart1[make_pair(smallerCoord + i, firstCoord.second)] += 1;
                    dotGridPart2[make_pair(smallerCoord + i, firstCoord.second)] += 1;
				}
            }
            else
            {
                if (((firstCoord.first < secondCoord.first) && (firstCoord.second < secondCoord.second))
                    || ((firstCoord.first > secondCoord.first) && (firstCoord.second > secondCoord.second)))
                {
                    diff = abs(firstCoord.first - secondCoord.first);
                    pair<int,int> startCoord = min(firstCoord.first, secondCoord.first) == firstCoord.first ? firstCoord : secondCoord;

                    for (int i = 0; i <= diff; i++)
                    {
                        dotGridPart2[make_pair(startCoord.first + i, startCoord.second + i)] += 1;
                    }
                }
                else
                {
                    diff = abs(firstCoord.first - secondCoord.first);
                    pair<int, int> startCoord = min(firstCoord.first, secondCoord.first) == firstCoord.first ? firstCoord : secondCoord;

					for (int i = 0; i <= diff; i++)
					{
						dotGridPart2[make_pair(startCoord.first + i, startCoord.second - i)] += 1;
					}
                }
            }
        }
    }

    int dangerousDots = 0;

    for (const auto& dot : dotGridPart1)
    {
        if (dot.second >= 2)
        {
            dangerousDots++;
        }
    }

    cout << "Part 1 - Number of points for horizontal and vertical lines : " << dangerousDots << endl;

	dangerousDots = 0;

	for (const auto& dot : dotGridPart2)
	{
		if (dot.second >= 2)
		{
			dangerousDots++;
		}
	}

    cout << "Part 2 - Number of points for all lines : " << dangerousDots << endl;

    return 0;
}