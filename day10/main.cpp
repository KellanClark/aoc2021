
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stack>
#include <fstream>
#include <algorithm>

int main() {
	std::fstream inFile("../day10/input", std::ios_base::in);

	std::vector<std::string> input;
	std::string line;
	while (inFile >> line)
		input.push_back(line);

	// Part 1/2
	unsigned score1 = 0;
	std::vector<unsigned long> scores2;
	for (auto i : input) {
		int error = 0;
		bool corrupted = false;
		std::stack<char> characters;

		for (char c : i) {
			switch (c) {
			case '(':
			case '[':
			case '{':
			case '<':
				characters.push(c);
				break;
			case ')':
				if (characters.top() == '(') {
					characters.pop();
				} else {
					error = 3;
					corrupted = true;
				}
				break;
			case ']':
				if (characters.top() == '[') {
					characters.pop();
				} else {
					error = 57;
					corrupted = true;
				}
				break;
			case '}':
				if (characters.top() == '{') {
					characters.pop();
				} else {
					error = 1197;
					corrupted = true;
				}
				break;
			case '>':
				if (characters.top() == '<') {
					characters.pop();
				} else {
					error = 25137;
					corrupted = true;
				}
				break;
			}

			if (corrupted) {
				score1 += error;
				break;
			}
		}
		
		if (!corrupted) {
			unsigned long score = 0;
			while (!characters.empty()) {
				score *= 5;
				switch (characters.top()) {
				case '(':
					score += 1;
					break;
				case '[':
					score += 2;
					break;
				case '{':
					score += 3;
					break;
				case '<':
					score += 4;
					break;
				}
				characters.pop();
			}
			std::cout << i << " " << error << " " << score << std::endl;
			scores2.push_back(score);
		}
	}
	printf("Part 1: %d\n", score1);
	
	std::sort(scores2.begin(), scores2.end());
	printf("Part 2: %zu\n", scores2[(scores2.size() / 2)]);

	return 0;
}