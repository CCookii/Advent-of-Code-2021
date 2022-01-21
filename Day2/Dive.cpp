#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
	ifstream input("input");
	string line;
	int x = 0, y = 0, aim = 0;
	while (input) {
		getline(input, line, ' ');
		int amount = input.get() - '0';
		input.get();
		if (line == "up")
			aim -= amount;
		else if (line == "down")
			aim += amount;
		else if (line == "forward") {
			x += amount;
			y += (aim * amount);
		}
	}
	cout << "End: " << (x * y) << endl;
}