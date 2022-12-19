#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

//I can't believe this compiles
struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

pair<int, int> moveTailIfNeeded(const pair<int, int> tailPos, const pair<int, int> headPos) {
	int firstDiff = tailPos.first - headPos.first;
	int secondDiff = tailPos.second - headPos.second;

	//adjacent
	if (abs(firstDiff) <= 1 && abs(secondDiff) <= 1)
		return tailPos;

	//lateral move
	else if (firstDiff == 0) {
		if (tailPos.second - 2 == headPos.second)
			return make_pair(tailPos.first, tailPos.second - 1);
		if (tailPos.second + 2 == headPos.second)
			return make_pair(tailPos.first, tailPos.second + 1);
	}

	else if (secondDiff == 0) {
		if (tailPos.first - 2 == headPos.first)
			return make_pair(tailPos.first - 1, tailPos.second);
		if (tailPos.first + 2 == headPos.first)
			return make_pair(tailPos.first + 1, tailPos.second);
	}

	//diagonal move
	if (abs(firstDiff) == 1) {
		if (tailPos.second - 2 == headPos.second)
			return make_pair(tailPos.first - firstDiff, tailPos.second - 1);
		if (tailPos.second + 2 == headPos.second)
			return make_pair(tailPos.first - firstDiff, tailPos.second + 1);
	}


	if (abs(secondDiff) == 1) {
		if (tailPos.first - 2 == headPos.first)
			return make_pair(tailPos.first - 1, tailPos.second - secondDiff);
		if (tailPos.first + 2 == headPos.first)
			return make_pair(tailPos.first + 1, tailPos.second - secondDiff);
	}

	if (secondDiff == -2) {
		if (firstDiff == -2)
			return make_pair(tailPos.first + 1, tailPos.second + 1);
		if (firstDiff == 2)
			return make_pair(tailPos.first - 1, tailPos.second + 1);
	}

	if (secondDiff == 2) {
		if (firstDiff == -2)
			return make_pair(tailPos.first + 1, tailPos.second - 1);
		if (firstDiff == 2)
			return make_pair(tailPos.first - 1, tailPos.second - 1);
	}

	cout << "Error: difference between tail and head too large!\n";
	cout << "Head: " << headPos.first << " " << headPos.second << endl;
	cout << "Tail: " << tailPos.first << " " << tailPos.second << endl;
	throw invalid_argument("Difference between tail and head too large");

}

void moveRope(vector<pair<int, int>>& knots, const char direction, const int numToMove, unordered_set<pair<int, int>, pair_hash>& tailPositions) {
	for (int i = 0; i < numToMove; ++i) {
		switch(direction) {
			case 'D':
				knots[0] = make_pair(knots.front().first, knots.front().second - 1);
				break;
			case 'U':
				knots[0] = make_pair(knots.front().first, knots.front().second + 1);
				break;
			case 'L':
				knots[0] = make_pair(knots.front().first - 1, knots.front().second);
				break;
			case 'R':
				knots[0] = make_pair(knots.front().first + 1, knots.front().second);
				break;
			default:
				cout << "Unrecognized direction: " << direction << endl;
				throw invalid_argument("Unrecognized direction!");
		}

		for (int j = 0; j < knots.size() - 1; ++j) {
			try {
				knots[j + 1] = moveTailIfNeeded(knots[j + 1], knots[j]);
			} catch (invalid_argument e) {
				cout << "Failed on index: " << j << endl;
				cout << "direction: " << direction << endl;
				cout << "numToMove: " << numToMove << endl;
				for (int k = 0; k < knots.size(); ++k) {
					cout << "knot " << k << ": " << knots[k].first << " " << knots[k].second << endl;
				}
				throw e;
			}
		}

		tailPositions.insert(knots.back());
	}
}

int main() {
	cout << "enter input filename: ";
	string inputFilename;
	cin >> inputFilename;
	cout << endl;
	char isPartOne;
	cout << "Part one y/n?: ";
	cin >> isPartOne;
	cout << endl;

	int numKnots = (isPartOne == 'y') ? 2 : 10;

	ifstream istream(inputFilename);

	unordered_set<pair<int, int>, pair_hash> tailPositions;
	pair<int, int> startPos = make_pair(0, 0);
	vector<pair<int, int>> knots(numKnots, startPos);

	tailPositions.insert(startPos);
	string input;

	while (!istream.eof()) {
		getline(istream, input);
		stringstream ss(input);
		int numToMove;
		char direction;
		ss >> direction >> numToMove;
		moveRope(knots, direction, numToMove, tailPositions);
	}

	cout << "Answer part one is: " << tailPositions.size() << endl;

}
