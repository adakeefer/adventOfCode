#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int playGamePartOne(char away, char home) {
	if ((away == 'A' && home == 'X') || (away == 'B' && home == 'Y') || (away == 'C' && home == 'Z'))
		return 3;
	else if ((away == 'A' && home == 'Y') || (away == 'B' && home == 'Z') || (away == 'C' && home == 'X'))
		return 6;

	return 0;
}

int playGamePartTwo(char away, char result) {
	if ((away == 'A' && result == 'X') || (away == 'B' && result == 'Z') || (away == 'C' && result == 'Y'))
		return 3;
	else if ((away == 'A' && result == 'Z') || (away == 'B' && result == 'Y') || (away == 'C' && result == 'X'))
		return 2;

	return 1;
}

long partOne(long total, char away, char home) {
	total += playGamePartOne(away, home);

	switch(home) {
		case 'X':
			total += 1;
			break;
		case 'Y':
			total += 2;
			break;
		case 'Z':
			total += 3;
			break;
		default:
			cout << "Error reading game! Char read: " << home << endl;
			break;
	}

	return total;
}

long partTwo(long total, char away, char result) {
	total += playGamePartTwo(away, result);

	switch(result) {
		case 'X':
			break;
		case 'Y':
			total += 3;
			break;
		case 'Z':
			total += 6;
			break;
		default:
			cout << "Error reading game! Char read: " << result << endl;
			break;
	}

	return total;
}

int main() {
	cout << "Please enter the input filename:\n";
	string inputFilename;
	cin >> inputFilename;

	long totalPartOne = 0;
	long totalPartTwo = 0;

	ifstream iStream(inputFilename);

	while(!iStream.eof()) {
		string curr;
		getline(iStream, curr);
		char first = curr[0];
		char second = curr[2];
		totalPartOne = partOne(totalPartOne, first, second);
		totalPartTwo = partTwo(totalPartTwo, first, second);
	}

	cout << "Total part one is: " << totalPartOne << endl;
	cout << "Total part two is: " << totalPartTwo << endl;

}