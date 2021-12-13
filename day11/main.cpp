
#include <stdio.h>
#include <iostream>
#include <fstream>

int input[12][12] = {0};
bool hasFlashed[12][12] = {0};

void tryFlash(int y, int x) {
	if (!hasFlashed[y][x]) {
		if (++input[y][x] >= 10) {
			hasFlashed[y][x] = true;
			tryFlash(y - 1, x - 1);
			tryFlash(y - 1, x);
			tryFlash(y - 1, x + 1);
			tryFlash(y, x - 1);
			tryFlash(y, x + 1);
			tryFlash(y + 1, x - 1);
			tryFlash(y + 1, x);
			tryFlash(y + 1, x + 1);
		}
	}
}

int main() {
	std::fstream inFile("../day11/input", std::ios_base::in);

	std::string line;
	for (int i = 1; i < 11; i++) {
		inFile >> line;
		for (int j = 1; j < 11; j++) {
			input[i][j] = line[j - 1] - '0';
		}
	}

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if ((i == 0) || (i == 11) || (j == 0) || (j == 11))
				hasFlashed[i][j] = true;
		}
	}

	// Part 1/2
	unsigned long flashes = 0;
	int lastFlashes = 1; // Must be non-zero
	int steps;
	for (steps = 0; (steps < 100) || (lastFlashes != 100); steps++) {
		for (int i = 1; i < 11; i++) {
			for (int j = 1; j < 11; j++) {
				tryFlash(i, j);
			}
		}

		lastFlashes = 0;
		for (int i = 1; i < 11; i++) {
			for (int j = 1; j < 11; j++) {
				if (input[i][j] >= 10) {
					input[i][j] = 0;
					hasFlashed[i][j] = false;

					++lastFlashes;
				}
			}
		}
		flashes += lastFlashes;

		if (steps == 99)
			printf("Part 1: %zu\n", flashes);
	}
	printf("Part 2: %d\n", steps);

	return 0;
}