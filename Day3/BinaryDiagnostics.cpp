#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <bitset>

using namespace std;

int partOne(const string& inputName) {
	ifstream input(inputName);
	vector<vector<int>> bitCount(12, vector<int>(2));
	while (input) {
		string line;
		getline(input, line);
		for (size_t i = 0; i < line.size(); i++) {
			bitCount[i][line[i] - '0']++;
		}
	}
	uint16_t gamma = 0;
	for (int i = 0; i < bitCount.size(); i++) {
		int n = bitCount.size() - 1 - i;
		if (bitCount[i][1] > bitCount[i][0])
			gamma += (1 << n);
	}
	uint16_t epsilon = 0x0FFF - gamma;
	return epsilon * gamma;
}

int partTwo(const string& inputName) {
	ifstream input(inputName);
	vector<bitset<12>> bitInput;

	while (input) {
		string line;
		getline(input, line);
		bitInput.push_back(bitset<12>(line));
	}

	int i = 11;
	while (i >= 0 && bitInput.size() > 1) {
		int oneCount = 0;
		for (bitset<12>&num : bitInput)
			if (num[i])
				oneCount++;

		//i is pos of curr bit
		int bit = 0; //most sign bit
		if (oneCount >= bitInput.size() - oneCount)
			bit++;

		size_t k = 0; //for every input keep if it has most sign bit
		while (k < bitInput.size() && bitInput.size() > 1) {
			if (bitInput[k][i] == bit)
				k++;
			else
				bitInput.erase(bitInput.begin() + k);
		}
		i--;
	}
	return bitInput[0].to_ulong();
}

int main() {
	int result = partTwo("input");
	cout << "oxRating: " << result << endl;
}