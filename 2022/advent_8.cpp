#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;


vector<vector<int>> parseTrees(ifstream& istream) {
	vector<vector<int>> trees;
	string line;
	while (!istream.eof()) {
		getline(istream, line);
		vector<int> vectorized;
		for (char c : line) {
			vectorized.push_back(c - '0');
		}
		trees.push_back(vectorized);
	}

	return trees;
}


long numTreesVisible(vector<vector<bool>>& canSee) {
	long ans = 0;
	for (auto v : canSee) {
		ans += count(v.begin(), v.end(), true);
	}
	return ans;
}

int highestScenicScore(vector<vector<int>>& scenicScores) {
	int maxElement = 0;
	for (auto v : scenicScores) {
		maxElement = max(maxElement, *max_element(v.begin(), v.end()));
	}
	return maxElement;
}

long partOne(vector<vector<int>>& trees) {
	int currMax;

	vector<vector<bool>> canSee(trees.size(), vector<bool>(trees.front().size(), false));

	for (int i = 0; i < trees.size(); ++i) {
		currMax = -1;
		for (int j = 0; j < trees[i].size(); ++j) {
			if (trees[i][j] > currMax) {
				currMax = trees[i][j];
				canSee[i][j] = true;
			}
		}
	}

	for (int i = 0; i < trees.size(); ++i) {
		currMax = -1;
		for (int j = trees[i].size() - 1; j >= 0; --j) {
			if (trees[i][j] > currMax) {
				currMax = trees[i][j];
				canSee[i][j] = true;
			}
		}
	}

	for (int i = 0; i < trees.front().size(); ++i) {
		currMax = -1;
		for (int j = 0; j < trees.size(); ++j) {
			if (trees[j][i] > currMax) {
				currMax = trees[j][i];
				canSee[j][i] = true;
			}
		}
	}

	for (int i = 0; i < trees.front().size(); ++i) {
		currMax = -1;
		for (int j = trees.size() - 1; j >= 0; --j) {
			if (trees[j][i] > currMax) {
				currMax = trees[j][i];
				canSee[j][i] = true;
			}
		}
	}

	return numTreesVisible(canSee);
}


int partTwo(vector<vector<int>>& trees) {
	vector<vector<int>> scenicScores(trees.size(), vector<int>(trees.front().size(), 1));

	for (int i = 0; i < trees.size(); ++i) {
		unordered_map<int, int> mostRecent;
		for (int j = 0; j < trees[i].size(); ++j) {
				int score = j;
				int curr = trees[i][j];
				for (int temp = curr; temp < 10; ++temp) {
					if (mostRecent.find(temp) != mostRecent.end()) {
						score = j - mostRecent[temp];
						break;
					}
				}
				scenicScores[i][j] *= score;
				mostRecent[curr] = j;
		}
	}

	for (int i = 0; i < trees.size(); ++i) {
		unordered_map<int, int> mostRecent;
		for (int j = trees[i].size() - 1; j >= 0; --j) {
				int score = trees[i].size() - j - 1;
				int curr = trees[i][j];
				for (int temp = curr; temp < 10; ++temp) {
					if (mostRecent.find(temp) != mostRecent.end()) {
						score = mostRecent[temp] - j;
						break;
					}
				}
				scenicScores[i][j] *= score;
				mostRecent[curr] = j;
		}
	}

	for (int i = 0; i < trees.front().size(); ++i) {
		unordered_map<int, int> mostRecent;
		for (int j = 0; j < trees.size(); ++j) {
				int score = j;
				int curr = trees[j][i];
				for (int temp = curr; temp < 10; ++temp) {
					if (mostRecent.find(temp) != mostRecent.end()) {
						score = j - mostRecent[temp];
						break;
					}
				}
				scenicScores[j][i] *= score;
				mostRecent[curr] = j;
		}
	}

	for (int i = 0; i < trees.front().size(); ++i) {
		unordered_map<int, int> mostRecent;
		for (int j = trees.size() - 1; j >= 0; --j) {
				int score = trees.size() - j - 1;
				int curr = trees[j][i];
				for (int temp = curr; temp < 10; ++temp) {
					if (mostRecent.find(temp) != mostRecent.end()) {
						score = mostRecent[temp] - j;
						break;
					}
				}
				scenicScores[j][i] *= score;
				mostRecent[curr] = j;
		}
	}

	return highestScenicScore(scenicScores);
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

	ifstream istream(inputFilename);
	vector<vector<int>> trees = parseTrees(istream);
	if (isPartOne == 'y')
		cout << "Answer part one is: " << to_string(partOne(trees)) << endl;
	else
		cout << "Answer part two is: " << to_string(partTwo(trees)) << endl;

}

