#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>

using namespace std;

using Card = vector<vector<uint8_t>>;

typedef struct _Bingo {
	Card card;
	int hor[5] = {0};
	int ver[5] = {0};
} Bingo;

bool checkCard(Bingo& bingo, uint8_t num) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (bingo.card[i][j] == num) {
				bingo.card[i][j] = 100;
				bingo.hor[i]++;
				bingo.ver[j]++;
				return true;
			}
		}
	}
	return false;
}

bool isBingo(Bingo& bingo) {
	int i = 0;
	while (i < 5 && bingo.hor[i] != 5 && bingo.ver[i] != 5) {
		i++;
	}
	return (i != 5);
}

int partOne(const string& fileName) {
	fstream file(fileName);

	vector<uint8_t> input;
	string line;
	getline(file, line);
	stringstream ss(line);

	while (ss) {
		getline(ss, line, ',');
		input.push_back(stoi(line));
	}
	file.get();

	vector<Bingo> cards;
	while (file) {
		Bingo bingo;
		bingo.card = Card(5, vector<uint8_t>(5, 0));
		char number[3];
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				file.get(number, 3);
				bingo.card[i][j] = stoi(number);
				file.get();
			}
		}
		cards.push_back(bingo);
		file.get();
	}

	Bingo* found = nullptr;
	uint8_t called = 0;
	for (uint8_t num : input) {
		for (Bingo& bingo : cards) {
			if (checkCard(bingo, num) && isBingo(bingo)) {
				found = &bingo;
				break;
			}
		}
		if (found) {
			called = num;
			break;
		}
	}


	int sum = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (found && found->card[i][j] != 100) {
				sum += found->card[i][j];
			}
		}
	}
	return sum * called;
}

int main() {
	int result = partOne("input");
	cout << "Result: " << result << endl;
}