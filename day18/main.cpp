
#include <iterator>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>

int main() {
	std::fstream inFile{"../day18/testinput", std::ios::in};

	std::list<char> input;
	auto readLine = [&](bool firstTime) -> bool {
		std::string readString;
		if (!(inFile >> readString))
			return false;

		if (!firstTime) [[likely]]
			input.push_front('[');

		for (char c : readString) {
			if ((c == '[') || (c == ']')) {
				input.push_back(c);
			} else if (c != ',') {
				input.push_back(c - '0');
			}
		}

		if (!firstTime) [[likely]]
			input.push_back(']');

		return true;
	};

	auto printState = [&]() {
		for (auto i = input.begin(); i != input.end(); i++) {
			if ((*i == '[') || (*i == ']')) {
				std::cout << *i;
			} else {
				std::cout << (int)*i;
			}

			if (*i != '[') {
				++i;
				if ((*i != ']') && (i != input.end()))
					std::cout << ',';
				--i;
			}
		}
		std::cout << std::endl;
	};

	// Part 1
	readLine(true);
	while (readLine(false)) {
		bool hasChanged = true;
		while (hasChanged) {
			printState();
			hasChanged = false;
			
			int depth = 0;
			for (auto curPos = input.begin(); (curPos != input.end()) && !hasChanged; curPos++) {
				if (*curPos == '[') {
					++depth;
				} else if (*curPos == ']') {
					--depth;
				} else { // Number
					auto nextPos = curPos;
					++nextPos;
					if ((depth > 4) && (*nextPos < '[')) { // Explode
						hasChanged = true;
						int leftNum = *curPos;
						int rightNum = *nextPos;

						// Erase old pair
						--curPos;
						std::advance(nextPos, 2);
						input.erase(curPos, nextPos);

						// Replace with 0
						curPos = input.insert(nextPos, 0);

						// Search backwards for left number
						while (curPos != input.begin()) {
							--curPos;
							if (*curPos < '[') {
								*curPos += leftNum;
								break;
							}
						}

						// Search forwards for left number
						while (nextPos != input.end()) {
							if (*nextPos < '[') {
								*nextPos += rightNum;
								break;
							}
							++nextPos;
						}
					} else if (*curPos > 9) { // Split
						hasChanged = true;
						int leftNum = *curPos / 2;
						int rightNum = (*curPos + 1) / 2;

						input.erase(curPos); // Erase old number

						// Insert new pair
						input.insert(nextPos, '[');
						input.insert(nextPos, leftNum);
						input.insert(nextPos, rightNum);
						input.insert(nextPos, ']');
					}
				}
			}
		}
	}
	printState();

	return 0;
}