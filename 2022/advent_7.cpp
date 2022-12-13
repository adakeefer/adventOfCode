#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

const string KNOWN_COMMANDS[] = {"cd", "ls"};
const string DIR_UP = "..";
const string DIR = "dir";
const string ROOT = "/";

const long DISK_SIZE = 70000000;
const long UPDATE_SPACE_REQUIRED = 30000000;
const long SIZE_LIMIT = 100000;

struct TreeNode {
	vector<TreeNode*> contents; //could use map but it's small input
	TreeNode* parent;
	string name;
	long size;
	bool isDir;

	TreeNode(string name, bool isDir, TreeNode* parent, long size) {
		this->name = name;
		this->isDir = isDir;
		this->parent = parent;
		this->size = size;
	}
};

TreeNode* cd(TreeNode* curr, string& target, TreeNode* root) {
	if (target == DIR_UP)
		return curr->parent;
	else if (target == ROOT)
		return root;

	for (auto file : curr->contents) {
		if (file->isDir && file->name == target)
			return file;
	}

	cout << "Cannot find dir: " << target << endl;
	throw invalid_argument("cant find dir");
}

void addFile(TreeNode* curr, string& filename, bool isDir, long size) {
	if (!curr->isDir) {
		cout << "warning: attempting to add file to non-directory\n";
		throw invalid_argument("cannot add to dir");
	}
	for (auto file : curr->contents) {
		if (file->name == filename) {
			cout << "duplicate filename: " << filename << " in dir " << curr->name << endl;
			throw invalid_argument("duplicate filename");
		}
	}

	TreeNode* newFile = new TreeNode(filename, isDir, curr, size);
	curr->contents.push_back(newFile);
}

void populateTreeSize(TreeNode* curr, long size) {
	if (!curr)
		return;
	curr->size += size;
	return populateTreeSize(curr->parent, size);
}

void ls(string& input, TreeNode* curr) {
	string first, second;
	stringstream ss(input);
	ss >> first >> second;

	if (first == DIR)
		addFile(curr, second, true, 0);
	else {
		long size = stol(first);
		addFile(curr, second, false, size);
		populateTreeSize(curr, size);
	}
}


string parseCommand(string& input) {
	string command, junk;
	stringstream ss(input);
	ss >> junk >> command;
	return command;
}

long calculatePartOne(TreeNode* root) {
	long size = 0;
	for (auto node : root->contents) {
		if (node->isDir)
			size += calculatePartOne(node);
	}

	if (root->size < SIZE_LIMIT)
		size += root->size;
	return size;
}

long partTwoHelper(TreeNode* root, long target) {
	long currBest = root->size;
	if (currBest >= target) {
		for (auto child : root->contents) {
			if (child->isDir)
				currBest = min(currBest, partTwoHelper(child, target));
		}
	} else {
		currBest = LONG_MAX;
	}

	return currBest;
}

long calculatePartTwo(TreeNode* root) {
	long unusedSpace = DISK_SIZE - root->size;
	long targetSpace = UPDATE_SPACE_REQUIRED - unusedSpace;
	if (unusedSpace < 0 || targetSpace < 0) {
		cout << "Error calculating file sizes - unusedSpace: " << unusedSpace << " targetSpace: " << targetSpace << endl;
		throw new invalid_argument("invalid file sizes");
	}

	return partTwoHelper(root, targetSpace);
}

void printTree(TreeNode* root) {
	if (root->isDir) {
		cout << root->name << " is directory and children are...\n";
		for (auto child : root->contents) {
			printTree(child);
		}
		cout << "Returned to root " << root->name << endl;
	} else {
		cout << "file: " << root->name << endl;
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

	ifstream istream(inputFilename);

	TreeNode* root = new TreeNode("/", true, nullptr, 0);
	TreeNode* curr = root;
	bool inLs = false;

	while (!istream.eof()) {
		string input;
		getline(istream, input);
		if (input[0] == '$')
			inLs = false;

		if (inLs) {
			ls(input, curr);
		} else {
			try {
				string command = parseCommand(input);
				if (command == KNOWN_COMMANDS[0]) {
					string arg = input.substr(5);
					curr = cd(curr, arg, root);
				} else if (command == KNOWN_COMMANDS[1]) {
					inLs = true;
				}
				else {
					cout << "error: unrecognized command: " << command << endl;
					throw invalid_argument("unrecognized command");
				}
			} catch (invalid_argument e) {
				printTree(root);
				throw e;
			}
		}
	}

	if (isPartOne == 'y')
		cout << "Answer part one is: " << calculatePartOne(root) << endl;
	else
		cout << "Answer part two is: " << calculatePartTwo(root) << endl;

}



