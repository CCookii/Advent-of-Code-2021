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
} BingoCard;

bool checkCard(BingoCard& bingoCard, uint8_t num) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (bingoCard.card[i][j] == num) {
				bingoCard.card[i][j] = 100;
				bingoCard.hor[i]++;
				bingoCard.ver[j]++;
				return true;
			}
		}
	}
	return false;
}

bool isBingo(BingoCard& bingoCard) {
	int i = 0;
	while (i < 5 && bingoCard.hor[i] != 5 && bingoCard.ver[i] != 5) {
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

	vector<BingoCard> cards;
	while (file) {
		BingoCard bingoCard;
		bingoCard.card = Card(5, vector<uint8_t>(5, 0));
		char number[3];
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				file.get(number, 3);
				bingoCard.card[i][j] = stoi(number);
				file.get();
			}
		}
		cards.push_back(bingoCard);
		file.get();
	}

	BingoCard* found = nullptr;
	uint8_t called = 0;
	for (uint8_t num : input) {
		for (BingoCard& bingoCard : cards) {
			if (checkCard(bingoCard, num) && isBingo(bingoCard)) {
				found = &bingoCard;
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

int partTwo(const string& fileName) {
	fstream file(fileName);

	vector<uint8_t> input;
	string line;
	getline(file, line);
	stringstream ss(line);

	//Get the input numbers
	while (ss) {
		getline(ss, line, ',');
		input.push_back(stoi(line));
	}
	file.get();

	//Get the input cards
	vector<BingoCard> cards;
	while (file) {
		BingoCard bingoCard;
		bingoCard.card = Card(5, vector<uint8_t>(5, 0));
		char number[3];
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				file.get(number, 3);
				bingoCard.card[i][j] = stoi(number);
				file.get();
			}
		}
		cards.push_back(bingoCard);
		file.get();
	}

	//Iterate over every input and check cards
	uint8_t called = 0;
	for (uint8_t num : input) {
		int i = 0;
		//While there are still cards
		while (i < cards.size()) {
			BingoCard& bingoCard = cards[i];
			//Check the card
			if (checkCard(bingoCard, num)) {
				//If it's not the last card and the card has a bingo, remove the card
				if (cards.size() > 1 && isBingo(bingoCard)) {
					cards.erase(cards.begin() + i);
					i--;
				}
			}
			i++;
		}

		if (isBingo(cards[0])) {
			called = num;
			break;
		}
	}


	int sum = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (cards[0].card[i][j] != 100) {
				sum += cards[0].card[i][j];
			}
		}
	}
	return sum * called;
}

int main() {
	int result = partTwo("input");
	cout << "Result: " << result << endl;
}