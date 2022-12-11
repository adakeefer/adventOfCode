#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

long partOne(string& line) {
	unordered_set<char> firstHalf;

	string first = line.substr(0, line.length() / 2);
	string second = line.substr(line.length() / 2);
	firstHalf.insert(first.begin(), first.end());

	long sum = 0;
	unordered_set<char> duplicates;
	for (char c : second) {
		if (firstHalf.find(c) != firstHalf.end())
			duplicates.insert(c);
	}

	for (char c : duplicates) {
		if (c < 'a')
			sum += (c - 'A' + 27);
		else
			sum += (c - 'a' + 1);
	}

	return sum;
}

long partTwo(string& line1, string& line2, string& line3) {
	unordered_set<char> firstSet(line1.begin(), line1.end());
	unordered_set<char> secondSet;

	for (char c : line2) {
		if (firstSet.find(c) != firstSet.end())
			secondSet.insert(c);
	}

	char badge;
	for (char c : line3) {
		if (secondSet.find(c) != secondSet.end()) {
			badge = c;
			break;
		}
	}

	return (badge < 'a') ? badge - 'A' + 27 : badge - 'a' + 1;
}

int main() {
	cout << "Enter input filename: \n";
	string inputFilename;
	cin >> inputFilename;

	cout << "Part one y/n?\n";
	char isPartOne;
	cin >> isPartOne;

	ifstream iStream(inputFilename);

	long sumPartOne = 0;
	long sumPartTwo = 0;

	if (isPartOne == 'y') {
		while (!iStream.eof()) {
			string line;
			getline(iStream, line);
			sumPartOne += partOne(line);
		}
	} else {
		while (!iStream.eof()) {
			string line1, line2, line3;
			getline(iStream, line1);
			getline(iStream, line2);
			getline(iStream, line3);
			sumPartTwo += partTwo(line1, line2, line3);
		}
	}

	cout << "Priority total part one is: " << sumPartOne << endl;
	cout << "Priority total part two is: " << sumPartTwo << endl;

}
