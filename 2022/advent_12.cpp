#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <stdexcept>
#include <stdlib.h>
#include <queue>
#include <climits>
#include <utility>

using namespace std;

const char GOAL = 'E';
const char TRUE_START = 'S';
const char START = 'a';
const char VISITED = '+';
const vector<pair<int, int>> VALID_DIRECTIONS = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

void reset(vector<vector<char>>& heightMap, const vector<vector<char>>& originals) {
	for (int i = 0; i < heightMap.size(); ++i) {
		for (int j = 0; j < heightMap[i].size(); ++j) {
			if (heightMap[i][j] == VISITED)
				heightMap[i][j] = originals[i][j];
		}
	}
}

bool isValidStep(int i, int j, char toCompare, vector<vector<char>>& heightMap) {
	return (i >= 0 && i < heightMap.size() && j >= 0 && j < heightMap.front().size()
		 && heightMap[i][j] != VISITED && ((toCompare == 'z' && heightMap[i][j] == GOAL) || (heightMap[i][j] != GOAL && heightMap[i][j] - toCompare <= 1)));
}

int findPath(int startI, int startJ, vector<vector<char>>& heightMap) {
	queue<pair<int, int>> bfs;
	bfs.push(make_pair(startI, startJ));
	int steps = 0;

	while (!bfs.empty()) {
		int size = bfs.size();
		for (int count = 0; count < size; ++count) {
			auto curr = bfs.front();
			int i = curr.first;
			int j = curr.second;
			if (heightMap[i][j] == GOAL)
				return steps;
			bfs.pop();
			for (auto dir : VALID_DIRECTIONS) {
				if (isValidStep(i + dir.first, j + dir.second, heightMap[i][j], heightMap)) {
					bfs.push(make_pair(i + dir.first, j + dir.second));
				}
			}
			heightMap[i][j] = VISITED;
		}

		++steps;
	}

	return INT_MAX;
}

int main() {
	cout << "it's part two! enter input filename: ";
	string inputFilename;
	cin >> inputFilename;
	cout << endl;

	ifstream istream(inputFilename);

	vector<vector<char>> heightMap;
	vector<pair<int, int>> startLocations;
	int rowCount = 0;
	while (!istream.eof()) {
		string temp;
		getline(istream, temp);
		vector<char> currLine(temp.length());
		for (int i = 0; i < temp.length(); ++i) {
			if (temp[i] == TRUE_START) {
				startLocations.push_back(make_pair(rowCount, i));
				currLine[i] = 'a';
			} else if (temp[i] == START) {
				startLocations.push_back(make_pair(rowCount, i));
				currLine[i] = temp[i];
			} else {
				currLine[i] = temp[i];
			}
		}
		heightMap.push_back(currLine);
		++rowCount;
	}

	const vector<vector<char>> originals(heightMap);

	int smallestPath = INT_MAX;

	for (auto loc : startLocations) {
		smallestPath = min(smallestPath, findPath(loc.first, loc.second, heightMap));
		reset(heightMap, originals);
	}

	if (smallestPath == INT_MAX)
		throw logic_error("Could not find a path!");

	cout << "Answer part two is: " << smallestPath << endl;
}
