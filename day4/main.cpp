
#include <bitset>
#include <cstdio>
#include <ios>
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <immintrin.h>

struct Board {
	union {
		unsigned char values[32];
		__m256i full;
	};
	unsigned selectedMask;
};

unsigned winConditions[16] __attribute__ ((aligned(64))) = {
	0b0000000'11111'00000'00000'00000'00000,
	0b0000000'00000'11111'00000'00000'00000,
	0b0000000'00000'00000'11111'00000'00000,
	0b0000000'00000'00000'00000'11111'00000,
	0b0000000'00000'00000'00000'00000'11111,
	0b0000000'10000'10000'10000'10000'10000,
	0b0000000'01000'01000'01000'01000'01000,
	0b0000000'00100'00100'00100'00100'00100,
	0b0000000'00010'00010'00010'00010'00010,
	0b0000000'00001'00001'00001'00001'00001,
	0b1111111'11111'11111'11111'11111'11111,
	0b1111111'11111'11111'11111'11111'11111,
	0b1111111'11111'11111'11111'11111'11111,
	0b1111111'11111'11111'11111'11111'11111,
	0b1111111'11111'11111'11111'11111'11111,
	0b1111111'11111'11111'11111'11111'11111,
};

int main() {
	__m512i winConditions512 = _mm512_load_epi32(winConditions);

	std::fstream inFile("../day4/input", std::ios_base::in);

	// Read list of chosen numbers
	std::vector<unsigned char> chosenNumbers;
	int readValue;
	char readChar;
	while (inFile >> readValue) {
		chosenNumbers.push_back(readValue);

		// Read until no comma (end of list)
		inFile >> std::noskipws >> readChar >> std::skipws;
		if (readChar != ',')
			break;
	}

	// Read boards
	std::vector<Board> boards;
	for (int i = 0; true; i++) {
		Board readBoard;
		readBoard.selectedMask = 0;
		for (int j = 31; j >= 0; j--) {
			if (j < 25) {
				inFile >> readValue;
				readBoard.values[j] = (unsigned char)readValue;
			} else {
				readBoard.values[j] = 0xFF;
			}
		}
		boards.push_back(readBoard);

		// Check if at end of file
		inFile >> std::noskipws >> readChar;
		if (!(inFile >> readChar >> std::skipws))
			break;
	}

	bool part1Done = false;
	for (int currentNumber = 0; currentNumber < chosenNumbers.size(); currentNumber++) {
		__m256i boardCompare = _mm256_set1_epi8(chosenNumbers[currentNumber]);

		for (int i = boards.size() - 1; i >= 0; i--) {
			boards[i].selectedMask |= _mm256_cmpeq_epi8_mask(boards[i].full, boardCompare);

			if (currentNumber >= 4) { // Ignore first 4 chosen numbers
				__m512i selected512 = _mm512_set1_epi32(boards[i].selectedMask);
				selected512 = _mm512_and_epi32(selected512, winConditions512);
				unsigned fulfilledWinConditions = _mm512_cmpeq_epi32_mask(selected512, winConditions512);

				if (fulfilledWinConditions) { // Board has won
					if (!part1Done) {
						// Because there's no _mm256_mask_reduce_add_epi16
						int total = 0;
						for (int j = 24; j >= 0; j--) {
							if (!((boards[i].selectedMask >> j) & 1)) {
								total += boards[i].values[j];
							}
						}

						printf("Part 1: %d\n", total * chosenNumbers[currentNumber]);
						part1Done = true;
					}
					if (boards.size() == 1) {
						int total = 0;
						for (int j = 24; j >= 0; j--) {
							if (!((boards[i].selectedMask >> j) & 1)) {
								total += boards[i].values[j];
							}
						}

						printf("Part 2: %d\n", total * chosenNumbers[currentNumber]);
					}
					boards.erase(boards.begin() + i);
				}
			}
		}
	}

	return 0;
}

/*
Boards stored as 32(25) packed 8bit values in mm256

generate 16(12) packed 32(25)bit win conditions in mm512

for each number:
broadcast 32 times to mm256 for compare value (_mm256_set1_epi8)

for each board:
compare equal to broadcasted value (compares each board number to chosen number) (_mm256_cmpeq_epi8_mask)
OR with 32 bit "selected" running mask

if checking at least the fifth chosen number:
broadcast 16 times to m512 (_mm512_set1_epi32)
AND with win conditions (_mm512_and_epi32)
compare to win conditions (_mm512_cmpeq_epi32_mask)
if not 0 that board wins

*/