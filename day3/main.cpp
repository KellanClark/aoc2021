
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <immintrin.h>

int main() {
	std::fstream inFile("../day3/input", std::ios_base::in);
	std::vector<short> input;
	std::string readString;
	while (inFile >> readString) {
		int convertedValue = 0;
		for (int i = 0; i < 12; i++)
			convertedValue |= (readString[11 - i] - '0') << i;

		input.push_back(convertedValue);
	}

	// Part 1
	__m256i bitCount = {0}; // Stores a 16-bit count of how many 1s in each column
	for (int i = 0; i < input.size(); i++) {
		__m256i expandedValue = _mm256_maskz_set1_epi16(input[i], 1); // Turn value into 16 values
		bitCount = _mm256_add_epi16(bitCount, expandedValue); // Add to running total
	}
	__m256i compareValue = _mm256_set1_epi16(input.size() / 2); // Compare every bit count to half the total count
	short gamma = _mm256_cmp_epi16_mask(bitCount, compareValue, _MM_CMPINT_GT);
	short epsilon = ~gamma & 0xFFF;
	printf("Part 1: %d\n", gamma * epsilon);

	// Part 2
	std::vector<short> oxygenBuff = input;
	std::vector<short> co2Buff = input;
	for (int bitPos = 11; (bitPos >= 0) && (oxygenBuff.size() != 1); bitPos--) {
		// Find most common bit
		int mostCommon = 0;
		for (auto val : oxygenBuff)
			mostCommon += (bool)(val & (1 << bitPos));
		bool equal = mostCommon == (oxygenBuff.size() / 2);
		mostCommon = mostCommon > (oxygenBuff.size() / 2);

		// Eliminate entries that don't fit
		for (int i = oxygenBuff.size() - 1; i >= 0; i--) {
			if (equal) {
				if (((oxygenBuff[i] >> bitPos) & 1) == 0)
					oxygenBuff.erase(oxygenBuff.begin() + i);
			} else {
				if (((oxygenBuff[i] >> bitPos) & 1) != mostCommon)
					oxygenBuff.erase(oxygenBuff.begin() + i);
			}
		}
	}
	int oxygenRating = oxygenBuff[0];
	for (int bitPos = 11; (bitPos >= 0) && (co2Buff.size() != 1); bitPos--) {
		// Find most common bit
		int leastCommon = 0;
		for (auto val : co2Buff)
			leastCommon += (bool)(val & (1 << bitPos));
		bool equal = leastCommon == (co2Buff.size() / 2);
		leastCommon = leastCommon < (co2Buff.size() / 2);

		// Eliminate entries that don't fit
		for (int i = co2Buff.size() - 1; i >= 0; i--) {
			if (equal) {
				if (((co2Buff[i] >> bitPos) & 1) == 1)
					co2Buff.erase(co2Buff.begin() + i);
			} else {
				if (((co2Buff[i] >> bitPos) & 1) != leastCommon)
					co2Buff.erase(co2Buff.begin() + i);
			}
		}
	}
	int co2Rating = co2Buff[0];
	printf("Part 2: %d\n", oxygenRating * co2Rating);

	return 0;
}