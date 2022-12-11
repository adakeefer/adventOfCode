#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>


using namespace std;

int process(ifstream& istream, int limit) {
	int pos = 1;
	unordered_map<char, int> counts;
	queue<char> curr;
	int numUnique = 0;

	while (!istream.eof()) {
		char c;
		istream >> c;
		if (counts[c] == 0)
			numUnique++;
		else if (counts[c] == 1)
			numUnique--;
		counts[c]++;
		curr.push(c);

		if (curr.size() > limit) {
			c = curr.front();
			curr.pop();
			counts[c]--;
			if (counts[c] == 1)
				numUnique++;
			else if (counts[c] == 0)
				numUnique--;
		}

		if (numUnique == limit)
			break;

		++pos;
	}

	return pos;
}

int main() {
	cout << "enter input filename: ";
	string inputFilename;
	cin >> inputFilename;
	cout << endl;
	int limit;
	cout << "enter limit: ";
	cin >> limit;
	cout << endl;
	cout << "limit is: " << limit << endl;

	ifstream istream(inputFilename);
	cout << "Answer is: " << process(istream, limit) << endl;
}