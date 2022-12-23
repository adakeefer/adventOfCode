#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

//ask kevin about this one
const long COMMON_MOD = (13 * 7 * 3 * 19 * 5 * 2 * 11 * 17);

class Monkey {
public:
	vector<long> items;
	long (*operation)(long);
	bool (*test)(long);

	Monkey(long (*operation)(long), bool (*test)(long)) {
		this->operation = operation;
		this->test = test;
	}

	void setSuccessMonkey(Monkey* successMonkey) {
		if (this == successMonkey)
			throw invalid_argument("Cannot throw to the same monkey");
		this->successMonkey = successMonkey;
	}

	void setFailureMonkey(Monkey* failureMonkey) {
		if (this == failureMonkey) 
			throw invalid_argument("Cannot throw to the same monkey");
		this->failureMonkey = failureMonkey;
	}

	void applyOperation() {
		for (int i = 0; i < items.size(); ++i) {
			items[i] = operation(items[i]) % COMMON_MOD;
		}
	}

	void throwItems() {
		for (auto item : items) {
			if (test(item))
				successMonkey->items.push_back(item);
			else
				failureMonkey->items.push_back(item);
		}
		items.clear();
	}

private:
	Monkey* successMonkey;
	Monkey* failureMonkey;
};

void playRound(vector<Monkey*>& monkeys, vector<long>& monkeyInspections) {
	for (int i = 0; i < monkeys.size(); ++i) {
		monkeyInspections[i] += monkeys[i]->items.size();
		monkeys[i]->applyOperation();
		monkeys[i]->throwItems();
	}
}

int main() {
	cout << "It's monkey business!\n";
	vector<Monkey*> monkeys(8);

	auto monkey0Op = [](long i) { return i * 11; };
	auto monkey0Test = [](long i) { return (i % 13 == 0); };
	monkeys[0] = new Monkey(monkey0Op, monkey0Test);
	monkeys[0]->items = { 71, 56, 50, 73 };

	auto monkey1Op = [](long i) { return i + 1; };
	auto monkey1Test = [](long i) { return (i % 7 == 0); };
	monkeys[1] = new Monkey(monkey1Op, monkey1Test);
	monkeys[1]->items = { 70, 89, 82 };
	monkeys[0]->setSuccessMonkey(monkeys[1]);

	auto monkey2Op = [](long i) { return i * i; };
	auto monkey2Test = [](long i) { return (i % 3 == 0); };
	monkeys[2] = new Monkey(monkey2Op, monkey2Test);
	monkeys[2]->items = { 52, 95 };

	auto monkey3Op = [](long i) { return i + 2; };
	auto monkey3Test = [](long i) { return (i % 19 == 0); };
	monkeys[3] = new Monkey(monkey3Op, monkey3Test);
	monkeys[3]->items = { 94, 64, 69, 87, 70 };
	monkeys[3]->setSuccessMonkey(monkeys[2]);
	monkeys[1]->setSuccessMonkey(monkeys[3]);

	auto monkey4Op = [](long i) { return i + 6; };
	auto monkey4Test = [](long i) { return (i % 5 == 0); };
	monkeys[4] = new Monkey(monkey4Op, monkey4Test);
	monkeys[4]->items = { 98, 72, 98, 53, 97, 51};
	monkeys[4]->setSuccessMonkey(monkeys[0]);
	monkeys[2]->setFailureMonkey(monkeys[4]);

	auto monkey5Op = [](long i) { return i + 7; };
	auto monkey5Test = [](long i) { return (i % 2 == 0); };
	monkeys[5] = new Monkey(monkey5Op, monkey5Test);
	monkeys[5]->items = { 79 };
	monkeys[5]->setFailureMonkey(monkeys[0]);
	monkeys[4]->setFailureMonkey(monkeys[5]);
	monkeys[2]->setSuccessMonkey(monkeys[5]);

	auto monkey6Op = [](long i) { return i * 7; };
	auto monkey6Test = [](long i) { return (i % 11 == 0); };
	monkeys[6] = new Monkey(monkey6Op, monkey6Test);
	monkeys[6]->items = { 77, 55, 63, 93, 66, 90, 88, 71 };
	monkeys[6]->setSuccessMonkey(monkeys[2]);
	monkeys[6]->setFailureMonkey(monkeys[4]);
	monkeys[1]->setFailureMonkey(monkeys[6]);
	monkeys[3]->setFailureMonkey(monkeys[6]);

	auto monkey7Op = [](long i) { return i + 8; };
	auto monkey7Test = [](long i) { return (i % 17 == 0); };
	monkeys[7] = new Monkey(monkey7Op, monkey7Test);
	monkeys[7]->items = { 54, 97, 87, 70, 59, 82, 59 };
	monkeys[7]->setSuccessMonkey(monkeys[1]);
	monkeys[7]->setFailureMonkey(monkeys[3]);
	monkeys[0]->setFailureMonkey(monkeys[7]);
	monkeys[5]->setSuccessMonkey(monkeys[7]);

	vector<long> monkeyInspections(8);

	for (int i = 0; i < 10000; ++i) {
		playRound(monkeys, monkeyInspections);
	}

	long highest = 0;
	long secondHighest = 0;
	for (auto i : monkeyInspections) {
		if (i > highest) {
			secondHighest = highest;
			highest = i;
		} else if (i > secondHighest) {
			secondHighest = i;
		}
	}

	cout << "Answer part two is: " << highest * secondHighest << endl;
	
}



