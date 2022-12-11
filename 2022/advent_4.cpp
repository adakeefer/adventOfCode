#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

struct Range {
	int lower;
	int upper;

	Range(int lowerIn, int upperIn) : lower(lowerIn), upper(upperIn) {}
};

bool contains(Range r1, Range r2) {
	return (r1.lower <= r2.lower && r2.upper <= r1.upper);
}

bool intersects(Range r1, Range r2) {
	return (r1.upper >= r2.lower && r1.lower <= r2.lower) || (r2.upper >= r1.lower && r2.lower <= r1.lower);
}

pair<Range, Range> parseRange(string& curr) {
	int currIndex = 0;
	int beginIndex = 0;
	while (curr[currIndex] != '-')
		++currIndex;
	int lower = stoi(curr.substr(0, currIndex));
	currIndex++;
	beginIndex = currIndex;
	while (curr[currIndex] != ',')
		++currIndex;
	int upper = stoi(curr.substr(beginIndex, currIndex));
	Range r1(lower, upper);

	currIndex++;
	beginIndex = currIndex;
	while (curr[currIndex] != '-')
		++currIndex;
	lower = stoi(curr.substr(beginIndex, currIndex));
	currIndex++;
	beginIndex = currIndex;
	upper = stoi(curr.substr(beginIndex));
	Range r2(lower, upper);

	return make_pair(r1, r2);
}

int partOne(ifstream& iStream) {
	int total = 0;
	while (!iStream.eof()) {
		string curr;
		getline(iStream, curr);
		pair<Range, Range> ranges = parseRange(curr);
		if (contains(ranges.first, ranges.second) || contains(ranges.second, ranges.first))
			total++;
	}

	return total;
}

int partTwo(ifstream& iStream) {
	int total = 0;
	while (!iStream.eof()) {
		string curr;
		getline(iStream, curr);
		pair<Range, Range> ranges = parseRange(curr);
		if (intersects(ranges.first, ranges.second))
			total++;
	}

	return total;
}

int main() {

	cout << "Enter the input filename: ";
	string inputFilename;
	cin >> inputFilename;
	cout << endl;
	cout << "partOne y/n? ";
	char isPartOne;
	cin >> isPartOne;
	cout << endl;

	ifstream iStream(inputFilename);
	long sumPartTwo = 0;
	if (isPartOne == 'y')
		cout << "Number of pairs in part one is: " << partOne(iStream) << endl;
	else
		cout << "Number of pairs in part two is: " << partTwo(iStream) << endl;
	
}
