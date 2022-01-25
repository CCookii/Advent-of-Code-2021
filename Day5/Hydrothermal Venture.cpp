#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <functional>

using namespace std;


class Coord {
public:
	Coord(uint16_t xx, uint16_t yy) : x(xx), y(yy) {};
	Coord(const Coord& other) : x(other.x), y(other.y) {};
	bool operator== (const Coord& other) const { return ((this->x == other.x) && (this->y == other.y)); };
	uint16_t x, y;
};

class CoordHasher {
public:

	size_t operator()(const Coord& c) const
	{
		hash<int> inthasher;
		return inthasher(c.x * 1000 + c.y);
	}
};

class Straight {
public:
	Straight(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) : start(x1, y1), end(x2, y2) {};
	//Straight(const Straight& other) : start(other.start), end(other.end) {};
	Coord start, end;
};

bool eq_coord(Coord a, Coord b) {
	return ((a.x == b.x) && (a.y == b.y));
}

// Define for answer to part one
// #define PART_ONE

int solve(const string& fileName) {
	ifstream input(fileName);
	vector<Straight> lines;
	//extract input
	while (input && isdigit(input.peek())) {
		string line;
		getline(input, line, ',');
		uint16_t x1 = stoi(line);
		getline(input, line, ' ');
		uint16_t y1 = stoi(line);
		getline(input, line, ' ');
		getline(input, line, ',');
		uint16_t x2 = stoi(line);
		getline(input, line);
		uint16_t y2 = stoi(line);
		lines.push_back(Straight(x1, y1, x2, y2));
	}

	unordered_map<Coord, uint16_t, CoordHasher> grid;
	for (Straight& rechte : lines) {
		int8_t dx = (rechte.end.x > rechte.start.x) ? 1 : -1;
		int8_t dy = (rechte.end.y > rechte.start.y) ? 1 : -1;
		if (rechte.start.x == rechte.end.x) {
			dx = 0;
		}
		else if (rechte.start.y == rechte.end.y) {
			dy = 0;
		}
#ifdef PART_ONE
		else {
			continue;
		}
#endif
		Coord point(rechte.start);
		while (dx * point.x <= dx * rechte.end.x && dy * point.y <= dy * rechte.end.y) {
			if (grid.find(point) == grid.end()) {
				grid[point] = 0;
			}
			grid[point] += 1;
			point.x += dx;
			point.y += dy;
		}
	}
	unordered_map<Coord, uint16_t, CoordHasher>::const_iterator it;
	uint16_t overlaps = 0;
	for (it = grid.begin(); it != grid.end(); it++) {
		overlaps += (it->second > 1) ? 1 : 0;
	}
	return overlaps;
}

int main() {
	int result = solve("input");
	cout << "Result: " << result << endl;
}