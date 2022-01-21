#include <fstream>
#include <stdint.h>
#include <iostream>
#include <vector>

using namespace std;

int partOne(string fileName) {
	ifstream input(fileName);
	uint16_t prevNum;
	input >> prevNum;
	uint16_t num = prevNum;
	int increaseCount = 0;
	while (input) {
		if (num - prevNum > 0)
			increaseCount++;
		prevNum = num;
		input >> num;
	}
	return increaseCount;
}

int partTwo(string fileName) {
	ifstream input(fileName);
	vector<uint16_t> nums;
	for (int i = 0; i < 4; i++) {
		uint16_t num;
		input >> num;
		nums.push_back(num);
	}
	int increaseCount = 0;
	while (input) {
		if (nums[3] - nums[0] > 0)
			increaseCount++;
		uint16_t num;
		input >> num;
		nums.erase(nums.begin());
		nums.push_back(num);
	}
}

int main(int argc, char* argv) {
	int increaseCount = partTwo("input");
	cout << "Number of increases: " << increaseCount << endl;
}