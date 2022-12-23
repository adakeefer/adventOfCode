#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

const string VALID_COMMANDS[] = {"noop", "addx"};
const set<int> TARGET_CYCLES = {40, 80, 120, 160, 200, 240};

void printIfTargetCycle(int clockCycle) {
	if (TARGET_CYCLES.find(clockCycle) != TARGET_CYCLES.end())
		cout << endl;
}

void printPixel(int clockCycle, int registerVal) {
	int normalizedVal;
	int previousVal = 0;
	for (auto i : TARGET_CYCLES) {
		if (clockCycle <= i) {
			normalizedVal = clockCycle - previousVal;
			break;
		}
		previousVal = i;
	}

	normalizedVal--;

	if (abs(normalizedVal - registerVal) <= 1)
		cout << '#';
	else
		cout << '.';

	printIfTargetCycle(clockCycle);
}


int main() {
	cout << "it's part two now! enter input filename: ";
	string inputFilename;
	cin >> inputFilename;
	cout << endl;

	ifstream istream(inputFilename);
	int clockCycle = 0;
	int registerVal = 1;
	string input, instr;

	while (!istream.eof() && clockCycle <= 240) {
		getline(istream, input);
		stringstream ss(input);
		ss >> instr;
		if (instr == VALID_COMMANDS[0]) {
			clockCycle++;
			printPixel(clockCycle, registerVal);
		} else if (instr == VALID_COMMANDS[1]) {
			clockCycle++;
			printPixel(clockCycle, registerVal);
			clockCycle++;
			printPixel(clockCycle, registerVal);
			int toAdd;
			ss >> toAdd;
			registerVal += toAdd;
		} else {
			cout << "Error parsing instruction! Instr: " << instr << endl;
			throw invalid_argument("Invalid instruction");
		}

	}


}
