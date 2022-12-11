#include <iostream>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

void partOne(priority_queue<long>& calories) {
	cout << "Part one, most calories: " << calories.top() << endl;
}

void partTwo(priority_queue<long>& calories) {
	long sum = 0;
	for (int i = 0; i < 3; ++i) {
		sum += calories.top();
		calories.pop();
	}

	cout << "Part two, most calories: " << sum << endl;
}


int main() {
	string inputFilename;
	cout << "Enter input filename:\n";
	cin >> inputFilename;
	ifstream infile(inputFilename);
	priority_queue<long> calories;

	string currLine = "default";
	long sum;
	while(!infile.eof()) {
		sum = 0;
		while (getline(infile, currLine) && !currLine.empty()) {
			sum += stol(currLine);
		}
		calories.push(sum);
	}

	partOne(calories);

	partTwo(calories);
}