
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	std::fstream inFile("../day2/input", std::ios_base::in);
	if (!inFile.is_open()) {
		printf("Could not open input file.");
		return 1;
	}

	struct InputStruct {
		std::string command;
		int num;
	};
	std::vector<InputStruct> input;
	std::string readString;
	int readNum;
	while (inFile >> readString) {
		inFile >> readNum;
		input.push_back({readString, readNum});
	}

	// Part 1
	int horizontal = 0;
	int depth = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i].command.compare("forward") == 0) {
			horizontal += input[i].num;
		} else if (input[i].command.compare("down") == 0) {
			depth += input[i].num;
		} else if (input[i].command.compare("up") == 0) {
			depth -= input[i].num;
		}
	}
	printf("Part 1: %d\n", horizontal * depth);

	// Part 2
	horizontal = 0;
	depth = 0;
	int aim = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i].command.compare("forward") == 0) {
			horizontal += input[i].num;
			depth += aim * input[i].num;
		} else if (input[i].command.compare("down") == 0) {
			aim += input[i].num;
		} else if (input[i].command.compare("up") == 0) {
			aim -= input[i].num;
		}
	}
	printf("Part 2: %d\n", horizontal * depth);

	return 0;
}