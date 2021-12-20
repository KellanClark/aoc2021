
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

int main() {
	std::fstream inFile{"../day20/input", std::ios::in};

	std::string readString;
	std::vector<bool> key;
	key.reserve(512);
	inFile >> readString;
	for (char c : readString)
		key.push_back(c == '#');

	int bufferSize = 55;

	std::vector<std::vector<bool>> grid;
	inFile >> readString;
	int rowLength = (bufferSize * 2) + readString.length();
	for (int i = 0; i < bufferSize; i++) {
		grid.push_back({});
		grid.back().resize(rowLength);
	}
	do {
		grid.push_back({});
		grid.back().reserve(rowLength);
		grid.back().resize(bufferSize);
		for (char c : readString)
			grid.back().push_back(c == '#');
		grid.back().resize(rowLength);
	} while (inFile >> readString);
	for (int i = 0; i < bufferSize; i++) {
		grid.push_back({});
		grid.back().resize(rowLength);
	}
	std::vector<std::vector<bool>> newGrid = grid; // Mainly for copying size

	for (int iteration = 0; iteration < 50; iteration++) {
		for (int y = 0; y < grid.size(); y++) {
			for (int x = 0; x < rowLength; x++) {
				int keyIndex = 0;

				auto tryPosition = [&](int x, int y) {
					keyIndex <<= 1;

					if ((x < 0) || (x >= rowLength) || (y < 0) || (y >= grid.size())) { // Check if out of grid
						keyIndex |= grid[0][0];
					} else {
						keyIndex |= grid[y][x];
					}
				};

				tryPosition(x - 1, y - 1);
				tryPosition(x    , y - 1);
				tryPosition(x + 1, y - 1);
				tryPosition(x - 1, y    );
				tryPosition(x    , y    );
				tryPosition(x + 1, y    );
				tryPosition(x - 1, y + 1);
				tryPosition(x    , y + 1);
				tryPosition(x + 1, y + 1);

				newGrid[y][x] = key[keyIndex];
			}
		}
		grid = newGrid;

		if (iteration == 1) {
			int totalPixels = 0;
			for (auto i : grid) {
				for (auto j : i) 
					totalPixels += j;
			}
			printf("Part 1: %d\n", totalPixels);
		}
	}

	int totalPixels = 0;
	for (auto i : grid) {
		for (auto j : i) 
			totalPixels += j;
	}
	printf("Part 2: %d\n", totalPixels);

	return 0;
}