#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parseInput(const string& inputFileName) {
	ifstream file(inputFileName);

	vector<int> input;
	string line;
	getline(file, line, ',');
	while (file) {
		input.push_back(stoi(line));
		getline(file, line, ',');
	}
	return input;
}

int partOne() {
	vector<int> input = parseInput("input");
	sort(input.begin(), input.end());
	int med = input.at(input.size() / 2);

	int sum = 0;
	for (auto it = input.begin(); it != input.end(); it++) {
		if (*it < med) {
			sum += med - *it;
		}
		else {
			sum += *it - med;
		}
	}

	return sum;
}

int partTwo() {
	vector<int> input = parseInput("input");

}

int main() {
	int result = partOne();
	cout << "Result: " << result << endl;
}