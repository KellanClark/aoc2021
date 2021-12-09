
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <array>

int main() {
	std::fstream inFile("../day9/input", std::ios_base::in);

	int input[102][102] = {0};
	std::string line;
	int lines = 1;
	while (inFile >> line) {
		int j = 1;
		for (char c : line) {
			input[lines][j] = c - '0';
			++j;
		}
		input[lines][0] = 9;
		input[lines][j] = 9;

		++lines;
	}
	for (int i = 0; i <= lines; i++) {
		for (int j = 0; j < 102; j++) {
			if ((i == 0) || (i == lines))
				input[i][j] = 9;
		}
	}

	// Part 1
	std::vector<std::array<int, 3>> lowPoints;
	int riskLevel = 0;
	for (int i = 1; i < 101; i++) {
		for (int j = 1; j < 101; j++) {
			int currentSpace = input[i][j];
			if ((currentSpace < input[i - 1][j]) && (currentSpace < input[i + 1][j]) && (currentSpace < input[i][j - 1]) && (currentSpace < input[i][j + 1])) {
				riskLevel += currentSpace + 1;
				
				lowPoints.push_back({i, j, 0});
			}
		}
	}
	printf("Part 1: %d\n", riskLevel);
	
	// Part 2
	auto explore = [&](auto&& explore, int y, int x) {
		if (input[y][x] >= 9) {
			return 0;
		} else {
			input[y][x] += 10;
			return 1 + explore(explore, y - 1, x) + explore(explore, y + 1, x) + explore(explore, y, x - 1) + explore(explore, y, x + 1);
		}
	};

	for (int i = 0; i < lowPoints.size(); i++) {
		lowPoints[i][2] = explore(explore, lowPoints[i][0], lowPoints[i][1]);
	}
	std::sort(lowPoints.begin(), lowPoints.end(), [](auto a, auto b) -> bool {
		return a[2] > b[2];
	});
	printf("Part 2: %d\n", lowPoints[0][2] * lowPoints[1][2] * lowPoints[2][2]);

	return 0;
}