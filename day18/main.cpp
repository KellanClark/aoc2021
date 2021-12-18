
#include <iterator>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

std::vector<std::list<int>> input;
std::list<int> problem;

void evaluate() {
	bool noExplosion = false;
	bool noSplit = false;
	bool hasChanged = true;
	bool checkExplode = true;
	while (!(noExplosion && noSplit)) {
		hasChanged = false;
		int depth = 0;
		for (auto curPos = problem.begin(); (curPos != problem.end()) && !hasChanged; curPos++) {
			if (*curPos == '[') {
				++depth;
			} else if (*curPos == ']') {
				--depth;
			} else { // Number
				auto nextPos = curPos;
				++nextPos;
				if (checkExplode && (depth > 4) && (*nextPos < '[')) { // Explode
					hasChanged = true;
					int leftNum = *curPos;
					int rightNum = *nextPos;

					// Erase old pair
					--curPos;
					std::advance(nextPos, 2);
					problem.erase(curPos, nextPos);

					// Replace with 0
					curPos = problem.insert(nextPos, 0);

					// Search backwards for left number
					while (curPos != problem.begin()) {
						--curPos;
						if (*curPos < '[') {
							*curPos += leftNum;
							break;
						}
					}

					// Search forwards for left number
					while (nextPos != problem.end()) {
						if (*nextPos < '[') {
							*nextPos += rightNum;
							break;
						}
						++nextPos;
					}
				} else if (!checkExplode && (*curPos > 9)) { // Split
					hasChanged = true;
					int leftNum = *curPos / 2;
					int rightNum = (*curPos + 1) / 2;

					problem.erase(curPos); // Erase old number

					// Insert new pair
					problem.insert(nextPos, '[');
					problem.insert(nextPos, leftNum);
					problem.insert(nextPos, rightNum);
					problem.insert(nextPos, ']');
				}
			}
		}

		if (hasChanged) {
			noExplosion = false;
			noSplit = false;
		}
		if (!checkExplode || (checkExplode && !hasChanged)) {
			if (checkExplode)
				noExplosion = true;
			if (!checkExplode && !hasChanged)
				noSplit = true;

			checkExplode = !checkExplode;
		}
	}
}

int computeMagnitude() {
	bool hasChanged = true;
	while (hasChanged && (problem.size() != 1)) {
		hasChanged = false;
		int depth = 0;
		for (auto curPos = problem.begin(); (curPos != problem.end()) && !hasChanged; curPos++) {
			if (*curPos == '[') {
				++depth;
			} else if (*curPos == ']') {
				--depth;
			} else { // Number
				auto nextPos = curPos;
				++nextPos;
				if ((*nextPos != '[') && (*nextPos != ']')) { // Taking a big risk here
					hasChanged = true;
					int tmpMag = (*curPos * 3) + (*nextPos * 2);
					--curPos;
					std::advance(nextPos, 2);
					problem.erase(curPos, nextPos);
					curPos = problem.insert(nextPos, tmpMag);
				}
			}
		}
	}

	return *problem.begin();
}

int main() {
	std::fstream inFile{"../day18/input", std::ios::in};

	std::string readString;
	while (inFile >> readString) {
		input.push_back({});
		for (char c : readString) {
			if ((c == '[') || (c == ']')) {
				input.back().push_back(c);
			} else if (c != ',') {
				input.back().push_back(c - '0');
			}
		}
	}

	auto readLine = [&](int index) {
		std::string readString;
		bool firstProblem = problem == std::list<int>{};

		if (!firstProblem) [[likely]]
			problem.push_front('[');

		problem.insert(problem.end(), input[index].begin(), input[index].end());

		if (!firstProblem) [[likely]]
			problem.push_back(']');
	};

	// Part 1
	for (int i = 0; i < input.size(); i++) {
		readLine(i);
		evaluate();
	}
	printf("Part 1: %d\n", computeMagnitude());

	// Part 2
	int maxMagnitude = 0;
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input.size(); j++) {
			if (i != j) {
				problem.clear();
				readLine(i);
				readLine(j);
				evaluate();

				int magnitude = computeMagnitude();
				if (magnitude > maxMagnitude)
					maxMagnitude = magnitude;
			}
		}
	}
	printf("Part 2: %d\n", maxMagnitude);

	return 0;
}