#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

#define TOTAL_DAYS 256

int main() {
	ifstream file("input");
	uint64_t stages[2][9] = { {0}, {0} };
	string token;
	getline(file, token, ',');
	while (file) {
		stages[0][stoi(token)]++;
		getline(file, token, ',');
	}

	int i = 1;
	uint64_t day;
	for (day = 0; day < TOTAL_DAYS - 7; day += 7) {
		cout << "Days passed: " << day << endl;
		int j;
		for (j = 0; j < 7; j++) {
			stages[i][j] = stages[1 - i][j] + stages[1 - i][(j + 7) % 9];
		}
		while (j < 9) {
			stages[i][j] = stages[1 - i][(j + 7) % 9];
			j++;
		}
		i = 1 - i;
	}

	while (day < TOTAL_DAYS) {
		cout << "Days passed: " << day << endl;
		for (int j = 0; j < 9; j++) {
			stages[i][(j + 8) % 9] = stages[1 - i][j];
		}
		stages[i][6] += stages[1 - i][0];
		i = 1 - i;
		day++;
	}
	uint64_t sum = 0;
	for (int j = 0; j < 9; j++) {
		sum += stages[1 - i][j];
	}
	cout << "Result: " << sum << endl;
}