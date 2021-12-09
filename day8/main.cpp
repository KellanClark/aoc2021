
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bit>

const unsigned segmentPatters[10] = {
	0b1110111, // 0
	0b0100100, // 1
	0b1011101, // 2
	0b1101101, // 3
	0b0101110, // 4
	0b1101011, // 5
	0b1111011, // 6
	0b0100101, // 7
	0b1111111, // 8
	0b1101111, // 9
};

struct Display {
	unsigned uniquePatterns[10];
	unsigned outputValues[4];
};

int main () {
	std::fstream inFile("../day8/input", std::ios_base::in);

	std::vector<Display> input;
	std::string readString;
	while (inFile.peek() != EOF) {
		Display tmpDisplay;

		for (int i = 0; i < 10; i++) {
			inFile >> readString;

			tmpDisplay.uniquePatterns[i] = 0;
			for (char c : readString)
				tmpDisplay.uniquePatterns[i] |= (1 << (c - 'a'));
		}
		inFile >> readString;
		for (int i = 0; i < 4; i++) {
			inFile >> readString;
			
			tmpDisplay.outputValues[i] = 0;
			for (char c : readString)
				tmpDisplay.outputValues[i] |= (1 << (c - 'a'));
		}

		input.push_back(tmpDisplay);
	}

	// Part 1
	int total1 = 0;
	for (auto i : input) {
		for (auto j : i.outputValues) {
			switch (std::popcount(j)) {
			case 2: // 1
			case 3: // 7
			case 4: // 4
			case 7: // 8
				++total1;
				break;
			}
		}
	}
	printf("Part 1: %d\n", total1);

	// Part 2

	// I should probably make this constexpr or use a different method entirely, but it's getting late and this works well enough
	unsigned hashes[10] = {0};
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			hashes[i] += std::popcount(segmentPatters[i] & segmentPatters[j]);
		}
	}

	int total2 = 0;
	for (auto display : input) {
		unsigned translatedNum = 0;
		for (auto output : display.outputValues) {
			unsigned translatedSegment = 0;
			for (int j = 0; j < 10; j++) {
				translatedSegment += std::popcount(output & display.uniquePatterns[j]);
			}

			for (int j = 0; j < 10; j++) {
				if (hashes[j] == translatedSegment) {
					translatedSegment = j;
					break;
				}
			}
			translatedNum = (translatedNum * 10) + translatedSegment;
		}
		std::cout << translatedNum << std::endl;
		total2 += translatedNum;
	}
	printf("Part 2: %d\n", total2);

	return 0;
}