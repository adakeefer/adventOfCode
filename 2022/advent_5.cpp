#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

void parseCrateLine(string& line, vector<stack<char>>& crates) {
	int crateIndex = 0;
	int parseIndex = 1;
	while (parseIndex < line.length()) {
		if (line[parseIndex] != ' ') {
			crates[crateIndex].push(line[parseIndex]);
		}
		crateIndex++;
		parseIndex += 4;
	}
}

vector<stack<char>> parseInitialConfig(ifstream& iStream) {
	vector<string> config;
	string input = "";
	while (input.empty() || input[1] != '1') {
		getline(iStream, input);
		config.push_back(input);
	}

	config.pop_back();
	int numStacks = input[input.length() - 2] - '0';
	vector<stack<char>> crates(numStacks);
	for (int i = config.size() - 1; i >= 0; --i) {
		parseCrateLine(config[i], crates);
	}

	return crates;
}

void executeInstructionPartOne(string& instr, vector<stack<char>>& crates) {
	string trash;
	int numToMove = 0, source = 0, dest = 0;
	istringstream ss(instr);
	ss >> trash >> numToMove >> trash >> source >> trash >> dest;
	for (int i = 0; i < numToMove; ++i) {
		crates[dest - 1].push(crates[source - 1].top());
		crates[source - 1].pop();
	}
}

void executeInstructionPartTwo(string& instr, vector<stack<char>>& crates) {
	string trash;
	int numToMove = 0, source = 0, dest = 0;
	istringstream ss(instr);
	ss >> trash >> numToMove >> trash >> source >> trash >> dest;
	stack<char> temp;
	for (int i = 0; i < numToMove; ++i) {
		temp.push(crates[source - 1].top());
		crates[source - 1].pop();
	}
	while (!temp.empty()) {
		crates[dest - 1].push(temp.top());
		temp.pop();
	}
}

int main() {
	cout << "enter the input filename: ";
	string inputFilename;
	cin >> inputFilename;
	cout << endl;
	cout << "part one y/n?: ";
	char isPartOne;
	cin >> isPartOne;
	cout << endl;

	ifstream iStream(inputFilename);
	vector<stack<char>> crates = parseInitialConfig(iStream);
	string curr;
	getline(iStream, curr);
	while(!iStream.eof()) {
		getline(iStream, curr);
		if (isPartOne == 'y')
			executeInstructionPartOne(curr, crates);
		else
			executeInstructionPartTwo(curr, crates);
	}

	string s = "";
	for (int i = 0; i < crates.size(); ++i) {
		s.push_back(crates[i].top());
	}

	cout << "output is: " << s << endl;

}