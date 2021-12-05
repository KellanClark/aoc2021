
#include <array>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>

int main() {
	std::fstream inFile("../day5/input", std::ios_base::in);

	// I couldn't find an easy way to dynamically allocate 2d arrays, so one big one it is.
	int *grid1 = new int[1000 * 1000] {0};
	int *grid2 = new int[1000 * 1000] {0};
	int total1 = 0;
	int total2 = 0;
	int x1, y1, x2, y2;
	char miscChar;
	while (inFile >> x1) {
		inFile >> miscChar;
		inFile >> y1;
		inFile >> miscChar;
		inFile >> miscChar;
		inFile >> x2;
		inFile >> miscChar;
		inFile >> y2;

		// Part 1/2
		int dx = std::clamp((x2 - x1), -1, 1);
		int dy = std::clamp((y2 - y1), -1, 1);
		for (int x = x1, y = y1; (x != (x2 + dx)) || (y != (y2 + dy)); x += dx, y += dy) {
			if ((dx == 0) || (dy == 0)) {
				if (++grid1[(y * 1000) + x] == 2)
					++total1;
			}
			if (++grid2[(y * 1000) + x] == 2)
				++total2;
		}
	}
	printf("Part 1: %d\n", total1);
	printf("Part 2: %d\n", total2);

	return 0;
}