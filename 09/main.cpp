#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<vector<int>> heightmap;
vector<unsigned int> basinSizes;
unsigned int currentBasinSize;

void ComputePart1()
{
	int sumRisksLowPoints = 0;

	for (unsigned int i = 0; i < heightmap.size(); i++)
	{
		for (unsigned int j = 0; j < heightmap[i].size(); j++)
		{
			if (j == 0)
			{
				if (i == 0)
				{
					if ((heightmap[i][j] < heightmap[i + 1][j]) && (heightmap[i][j] < heightmap[i][j + 1]))
					{
						sumRisksLowPoints += 1 + heightmap[i][j];
					}
				}
				else if (i == heightmap.size() - 1)
				{
					if ((heightmap[i][j] < heightmap[i - 1][j]) && (heightmap[i][j] < heightmap[i][j + 1]))
					{
						sumRisksLowPoints += 1 + heightmap[i][j];
					}
				}
				else
				{
					if ((heightmap[i][j] < heightmap[i - 1][j]) && (heightmap[i][j] < heightmap[i][j + 1]) && (heightmap[i][j] < heightmap[i + 1][j]))
					{
						sumRisksLowPoints += 1 + heightmap[i][j];
					}
				}
			}
			else if (j == heightmap[i].size() - 1)
			{
				if (i == 0)
				{
					if ((heightmap[i][j] < heightmap[i + 1][j]) && (heightmap[i][j] < heightmap[i][j - 1]))
					{
						sumRisksLowPoints += 1 + heightmap[i][j];
					}
				}
				else if (i == heightmap.size() - 1)
				{
					if ((heightmap[i][j] < heightmap[i - 1][j]) && (heightmap[i][j] < heightmap[i][j - 1]))
					{
						sumRisksLowPoints += 1 + heightmap[i][j];
					}
				}
				else
				{
					if ((heightmap[i][j] < heightmap[i - 1][j]) && (heightmap[i][j] < heightmap[i][j - 1]) && (heightmap[i][j] < heightmap[i + 1][j]))
					{
						sumRisksLowPoints += 1 + heightmap[i][j];
					}
				}
			}
			else
			{
				if (i == 0)
				{
					if ((heightmap[i][j] < heightmap[i + 1][j]) && (heightmap[i][j] < heightmap[i][j - 1]) && (heightmap[i][j] < heightmap[i][j + 1]))
					{
						sumRisksLowPoints += 1 + heightmap[i][j];
					}
				}
				else if (i == heightmap.size() - 1)
				{
					if ((heightmap[i][j] < heightmap[i - 1][j]) && (heightmap[i][j] < heightmap[i][j - 1]) && (heightmap[i][j] < heightmap[i][j + 1]))
					{
						sumRisksLowPoints += 1 + heightmap[i][j];
					}
				}
				else
				{
					if ((heightmap[i][j] < heightmap[i - 1][j]) && (heightmap[i][j] < heightmap[i][j - 1]) && (heightmap[i][j] < heightmap[i + 1][j]) && (heightmap[i][j] < heightmap[i][j + 1]))
					{
						sumRisksLowPoints += 1 + heightmap[i][j];
					}
				}
			}
		}
	}

	cout << "Part 1 - The sum of the risk levels of all low points is " << sumRisksLowPoints << "." << endl;
}

void ExploreSurroundings(int vertIdx, int horizIndx)
{
	if ((heightmap[vertIdx][horizIndx] != 9) && (heightmap[vertIdx][horizIndx] != -1))
	{
		currentBasinSize += 1;
		heightmap[vertIdx][horizIndx] = -1;
	}
	else
	{
		return;
	}

	if ((horizIndx > 0) && (heightmap[vertIdx][horizIndx-1] != 9) && (heightmap[vertIdx][horizIndx - 1] != -1))
	{
		ExploreSurroundings(vertIdx, horizIndx - 1);
	}
	if ((vertIdx < heightmap.size() - 1) && (heightmap[vertIdx + 1][horizIndx] != 9) && (heightmap[vertIdx + 1][horizIndx] != -1))
	{
		ExploreSurroundings(vertIdx + 1, horizIndx);
	}
	if ((horizIndx < heightmap[vertIdx].size() - 1) && (heightmap[vertIdx][horizIndx + 1] != 9) && (heightmap[vertIdx][horizIndx + 1] != -1))
	{
		ExploreSurroundings(vertIdx, horizIndx + 1);
	}
	if ((vertIdx > 0) && (heightmap[vertIdx - 1][horizIndx] != 9) && (heightmap[vertIdx - 1][horizIndx] != -1))
	{
		ExploreSurroundings(vertIdx - 1, horizIndx);
	}

	return;
}

void ComputePart2()
{
	for (unsigned int i = 0; i < heightmap.size(); i++)
	{
		for (unsigned int j = 0; j < heightmap[i].size(); j++)
		{
			ExploreSurroundings(i, j);
			if (currentBasinSize > 0)
			{
				basinSizes.push_back(currentBasinSize);
			}
			currentBasinSize = 0;
		}
	}
	
	sort(basinSizes.begin(), basinSizes.end());

	if (basinSizes.size() >= 3)
	{
		unsigned int result = basinSizes[basinSizes.size() - 1] * basinSizes[basinSizes.size() - 2] * basinSizes[basinSizes.size() - 3];

		cout << "Part 2 - The multiplication of the size of the three largest basins equals " << result << "." << endl;
	}
	else
	{
		cout << "wtf bro (too few basins sizes)" << endl;
	}
}

int main()
{
	string inputLine;
	ifstream inputFile("input.txt");

	while (getline(inputFile, inputLine))
	{
		if (!inputLine.empty())
		{
			vector<int> heightLine;
			for (const auto& heightChar : inputLine)
			{
				heightLine.push_back(heightChar - '0');
			}

			heightmap.push_back(heightLine);
		}
	}

	ComputePart1();
	ComputePart2();
	return 0;
}