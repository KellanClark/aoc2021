
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

int main() {
	std::fstream inFile("../day1/input", std::ios_base::in);
	if (!inFile.is_open()) {
		printf("Could not open input file.");
		return 1;
	}

	std::vector<int> input;
	int readValue;
	while (inFile >> readValue)
		input.push_back(readValue);

	// Part 1
	int increaseNum = 0;
	for (int i = 1; i < input.size(); i++) {
		if (input[i] > input[i - 1])
			++increaseNum;
	}
	printf("Part 1: %d\n", increaseNum);

	int lastSum = input[0] + input[1] + input[2];
	increaseNum = 0;
	for (int i = 1; i < (input.size() - 2); i++) {
		int currentSum = input[i] + input[i + 1] + input[i + 2];
		if (currentSum > lastSum)
			++increaseNum;
		lastSum = currentSum;
	}
	printf("Part 2: %d\n", increaseNum);

	return 0;
}