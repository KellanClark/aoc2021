
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <queue>
#include <algorithm>
#include <numeric>
#include <vector>

std::queue<bool> buffer;
int versionTotal = 0;

unsigned getBits(int amount) {
	unsigned retVal = 0;
	for (; amount > 0; --amount) {
		retVal = (retVal << 1) | buffer.front();
		buffer.pop();
	}
	return retVal;
}

unsigned long parsePacket() {
	versionTotal += getBits(3);
	int typeId = getBits(3);

	if (typeId == 4) { // Literal Value
		unsigned long value = 0;

		int segment;
		do {
			segment = getBits(5);
			value = (value << 4) | (segment & 0xF);
		} while (segment & 0x10);

		return value;
	} else { // Operator
		std::vector<unsigned long> operands = {};

		if (getBits(1)) { // Number of sub packets
			int numPackets = getBits(11);
			for (int i = 0; i < numPackets; i++) {
				operands.push_back(parsePacket());
			}
		} else { // Bit length of sub packets
			int targetSize = getBits(15);
			targetSize = buffer.size() - targetSize;
			while (buffer.size() > targetSize) {
				operands.push_back(parsePacket());
			}
		}

		switch (typeId) {
		case 0: // Sum
			return std::accumulate(operands.begin(), operands.end(), (unsigned long)0);
		case 1: // Product
			return std::accumulate(operands.begin(), operands.end(), (unsigned long)1, std::multiplies<unsigned long>());
		case 2: // Minimum
			return *std::min_element(operands.begin(), operands.end());
		case 3: // Maximum
			return *std::max_element(operands.begin(), operands.end());
		case 5: // Greater Than
			return operands[0] > operands[1];
		case 6: // Less Than
			return operands[0] < operands[1];
		case 7: // Equal To
			return operands[0] == operands[1];
		}
	}
}

int main() {
	std::fstream inFile{"../day16/input", std::ios::in};

	std::string readString;
	inFile >> readString;
	for (char c : readString) {
		int num = c > '9' ? ((c - 'A') + 10) : (c - '0');

		buffer.push((num >> 3) & 1);
		buffer.push((num >> 2) & 1);
		buffer.push((num >> 1) & 1);
		buffer.push((num >> 0) & 1);
	}

	// Part 1/2
	printf("Part 2: %lu\n", parsePacket());
	printf("Part 1: %d\n", versionTotal);

	return 0;
}