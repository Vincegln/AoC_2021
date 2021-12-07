#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct boardCellData
{
    int boardNumber = -1;
    pair<int,int> cellCoordinates;
};

vector<int> ParseStringToInts(string& inputString, string delimiter)
{
    vector<int> results;
    
    auto start = 0U;
    auto end = inputString.find(delimiter);
    while (end != string::npos)
    {
        if(!inputString.substr(start, end - start).empty())
        {
            results.push_back(stoi(inputString.substr(start, end - start)));
        }
        start = end + delimiter.length();
        end = inputString.find(delimiter, start);
    }
    results.push_back(stoi(inputString.substr(start, end)));
    
    return results;
}

int CheckBoardsForWinner(map<int,vector<pair<int,int>>>& drawnCells, int boardCount, vector<int> completedBoards)
{
    map<int,vector<pair<int,int>>>::iterator it;
    
    int columnCount = -1;
    int rowCount = -1;
    
    for(int i = 0; i < boardCount; i++)
    {
        if (find(completedBoards.begin(), completedBoards.end(), i) == completedBoards.end())
        {
            it = drawnCells.find(i);

            if (it != drawnCells.end())
            {
                for (unsigned int j = 0; j < it->second.size(); j++)
                {
                    if (it->second[j].first == 0 || it->second[j].second == 0)
                    {
						columnCount = 1;
						rowCount = 1;
                        for (unsigned int k = 0; k < it->second.size(); k++)
                        {
							if ((it->second[j].first == it->second[k].first) && (it->second[j].second != it->second[k].second))
							{
								columnCount++;
							}
							else if ((it->second[j].second == it->second[k].second) && (it->second[j].first != it->second[k].first))
							{
								rowCount++;
							}

							if ((columnCount == 5) || (rowCount == 5))
							{
								return it->first;
							}
                        }
                    }
                }
            }
        }
    }
    
    return -1;
}

int SumOfUnmarkedCells(multimap<int,boardCellData>& boardCells, int boardNumber, vector<pair<int,int>>& markedCells)
{
    int sum = 0;
    
    for (multimap<int,boardCellData>::iterator it = boardCells.begin(); it != boardCells.end(); ++it) 
    {
        if(it->second.boardNumber == boardNumber)
        {
            pair<int,int> coordinates = it->second.cellCoordinates;
            vector<pair<int,int>>::iterator it2 = find_if(markedCells.begin(), markedCells.end(), [coordinates](pair<int,int>& drawnPair) -> bool { return ((coordinates.first == drawnPair.first) && (coordinates.second == drawnPair.second)); });
            if(it2 == markedCells.end())
            {
                sum += it->first; 
            }
        }
    }
    
    return sum;
}

int main()
{
    string inputLine;
    ifstream inputFile("input.txt");
    
    getline (inputFile, inputLine);

//Get draw order
    vector<int> draws = ParseStringToInts(inputLine, ",");
    
//Get boards
    int boardCount = -1;
    int lineCount = 0;
    multimap<int,boardCellData> boardCells;
    
    while(getline (inputFile, inputLine))
    {
        if(!inputLine.empty())
        {
            vector<int> boardLine = ParseStringToInts(inputLine, " ");
            for(unsigned int i =0; i < boardLine.size(); i++)
            {
                boardCellData boardCell;
                boardCell.boardNumber = boardCount;
                boardCell.cellCoordinates = make_pair(i,lineCount);
                
                boardCells.insert({boardLine[i],boardCell});
            }
            lineCount++;
        }
        else
        {
            boardCount++;
            lineCount = 0;
        }
    }
    
    map<int,vector<pair<int,int>>> drawnCells;
    map<int,vector<pair<int,int>>>::iterator it;
    int winningBoard = -1;
    bool firstWinAchieved = false;
    vector<int> completedBoards;
    int finalScore = -1;
    
    for(unsigned int i = 0; i < draws.size(); i++)
    {
        auto range = boardCells.equal_range(draws[i]);
 
        for (auto cellDataIterator = range.first; cellDataIterator != range.second; ++cellDataIterator)
        {
            it = drawnCells.find(cellDataIterator->second.boardNumber);
            if(it != drawnCells.end())
            {
                it->second.push_back(cellDataIterator->second.cellCoordinates);
            }
            else
            {
                vector<pair<int,int>> vect {cellDataIterator->second.cellCoordinates};
                drawnCells.insert({cellDataIterator->second.boardNumber,vect});
            }
        }
        
        do 
        {
            winningBoard = CheckBoardsForWinner(drawnCells, boardCount, completedBoards);

			if (winningBoard != -1)
			{
				int sum = SumOfUnmarkedCells(boardCells, winningBoard, drawnCells.find(winningBoard)->second);

                /*cout << "Draw n°" << i << ":" << draws[i] << endl;
				cout << winningBoard << endl;
				cout << sum << endl;
				cout << draws[i] * sum << endl << endl;*/

				if (!firstWinAchieved)
				{
					cout << "Part 1 - Score of first winning board : " << draws[i] * sum << endl;
					firstWinAchieved = true;
				}

                finalScore = draws[i] * sum;

				completedBoards.push_back(winningBoard);
			}
        } while (winningBoard != -1);
        
    }
    
    cout << "Part 2 - Score of last winning board : " << finalScore << endl;

    return 0;
}