
#include <iostream>
#include <fstream>
#include <stdio.h>

int main() {
	std::fstream inFile{"../day14/input", std::ios::in};

	unsigned long pairs[4096] = {0};
	long newPairs[4096] = {0};
	unsigned long counts[64] = {0};
	std::string readString;
	inFile >> readString;
	for (int i = 1; i < readString.length(); i++) {
		++pairs[((readString[i - 1] & 0x3F) << 6) | (readString[i] & 0x3F)];
		++counts[readString[i] & 0x3F];
	}
	++counts[readString[0] & 0x3F];

	char replacements[4096] = {0};
	char readChar;
	while (inFile >> readString) {
		inFile.ignore(4);
		inFile >> readChar;

		replacements[((readString[0] & 0x3F) << 6) | (readString[1] & 0x3F)] = readChar & 0x3F;
	}

	// Part 1/2
	auto difference = [&]() -> unsigned long {
		unsigned long mostCommon = 0;
		unsigned long leastCommon = -1;
		for (auto i : counts) {
			if (i) {
				if (i > mostCommon)
					mostCommon = i;
				if (i < leastCommon)
					leastCommon = i;
			}
		}
		return mostCommon - leastCommon;
	};

	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 4096; j++) {
			char newChar = replacements[j];
			if (pairs[j] && newChar) { // Ignore if 0 pairs or no replacements
				newPairs[j] -= pairs[j];
				newPairs[(j & (0x3F << 6)) | newChar] += pairs[j];
				newPairs[(newChar << 6) | (j & 0x3F)] += pairs[j];
				counts[newChar] += pairs[j];
			}
		}

		for (int j = 0; j < 4096; j++) {
			pairs[j] += newPairs[j];
			newPairs[j] = 0;
		}

		if (i == 9)
			printf("Part 1: %lu\n", difference());
	}
	printf("Part 2: %lu\n", difference());

	return 0;
}