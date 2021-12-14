
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <array>

int main() {
	std::fstream inFile{"../day13/input", std::ios::in};
	
	std::vector<std::array<int, 2>> points; // x, y
	std::vector<std::array<int, 2>> folds; // dimension, location
	int readNum1, readNum2;
	while (inFile >> readNum1) {
		inFile.ignore(1);
		inFile >> readNum2;
		
		points.push_back({readNum1, readNum2});
	}
	inFile.clear();
	inFile.ignore(11);
	char readChar;
	while (inFile >> readChar) {
		inFile.ignore(1);
		inFile >> readNum1;
		inFile.ignore(11);

		folds.push_back({readChar - 'x', readNum1});
	}
	int xSize = 0;
	int ySize = 0;
	for (auto i : points) {
		if (i[0] > xSize)
			xSize = i[0];
		if (i[1] > ySize)
			ySize = i[1];
	}
	++xSize;
	++ySize;

	// Part 1/2
	int visiblePoints = 0;
	bool grid[ySize][xSize] = {0};
	for (auto f : folds) {
		for (int p = 0; p < points.size(); p++) {
			int newX = points[p][0];
			int newY = points[p][1];
			if (f[0] && (points[p][1] > f[1])) { // Y flip
				points[p][1] = f[1] - (points[p][1] - f[1]);
				ySize = f[1];
			} else if (!f[0] && (points[p][0] > f[1])) { // X flip
				points[p][0] = f[1] - (points[p][0] - f[1]);
				xSize = f[1];
			}

			grid[points[p][1]][points[p][0]] = true;
		}

		if (visiblePoints == 0) {
			for (int i = 0; i < ySize; i++)
				for (int j = 0; j < xSize; j++)
					visiblePoints += grid[i][j];
		}
	}
	printf("Part 1: %d\n", visiblePoints);
	printf("Part 2:\n");
	for (int i = 0; i < ySize; i++) {
		for (int j = 0; j < xSize; j++) {
			putchar(grid[i][j] ? '#' : ' ');
		}
		putchar('\n');
	}

	return 0;
}