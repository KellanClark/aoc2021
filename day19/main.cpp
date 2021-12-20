
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

struct Point { // I could use an array, but this is more readable
	int x, y, z;

	bool operator< (const Point &right) const {
		if (this->x < right.x) {
			return true;
		} else if (this->y < right.y) {
			return true;
		} else if (this->z < right.z) {
			return true;
		} else {
			return false;
		}
	}

	bool operator==(const Point &right) const {
		return (this->x == right.x) && (this->y == right.y) && (this->z == right.z);
	}
};

Point (*(rotations[24]))(Point) = {
	[](Point in) {return (Point){ in.x,  in.y,  in.z};},
	[](Point in) {return (Point){ in.x,  in.z, -in.y};},
	[](Point in) {return (Point){ in.x, -in.y, -in.z};},
	[](Point in) {return (Point){ in.x, -in.z,  in.y};},
	[](Point in) {return (Point){ in.y, -in.x,  in.z};},
	[](Point in) {return (Point){ in.y,  in.z,  in.x};},
	[](Point in) {return (Point){ in.y,  in.x, -in.z};},
	[](Point in) {return (Point){ in.y, -in.z, -in.x};},
	[](Point in) {return (Point){-in.x, -in.y,  in.z};},
	[](Point in) {return (Point){-in.x, -in.z, -in.y};},
	[](Point in) {return (Point){-in.x,  in.y, -in.z};},
	[](Point in) {return (Point){-in.x,  in.z,  in.y};},
	[](Point in) {return (Point){-in.y,  in.x,  in.z};},
	[](Point in) {return (Point){-in.y, -in.z,  in.x};},
	[](Point in) {return (Point){-in.y, -in.x, -in.z};},
	[](Point in) {return (Point){-in.y,  in.z, -in.x};},
	[](Point in) {return (Point){ in.z,  in.y, -in.x};},
	[](Point in) {return (Point){ in.z,  in.x,  in.y};},
	[](Point in) {return (Point){ in.z, -in.y,  in.x};},
	[](Point in) {return (Point){ in.z, -in.x, -in.y};},
	[](Point in) {return (Point){-in.z, -in.y, -in.x};},
	[](Point in) {return (Point){-in.z, -in.x,  in.y};},
	[](Point in) {return (Point){-in.z,  in.y,  in.x};},
	[](Point in) {return (Point){-in.z,  in.x, -in.y};},
};

int main() {
	std::fstream inFile{"../day19/testinput", std::ios::in};

	std::vector<std::vector<Point>> input;
	std::string tmpString;
	int readX, readY, readZ;
	while (!inFile.eof()) {
		inFile.clear();
		input.push_back({});
		std::getline(inFile, tmpString); // Ignore first line

		while (inFile >> readX) {
			inFile.ignore(1);
			inFile >> readY;
			inFile.ignore(1);
			inFile >> readZ;

			input.back().push_back({readX, readY, readZ});
		}
	}

	// Make all coordinates from the first scanner known
	std::vector<Point> knownPoints = input[0];
	std::sort(knownPoints.begin(), knownPoints.end() - 1, [](const auto &left, const auto &right) {
		return (bool)left.x;
		if (left.x < right.x) {
			return true;
		} else if (left.y < right.y) {
			return true;
		} else if (left.z < right.z) {
			return true;
		} else {
			return false;
		}
	});
	input.erase(input.begin());
	std::vector<Point> convertedPoints;

	while (input.size() != 0) {
		for (int scanner = (input.size() - 1); scanner >= 0; scanner--) {
			bool found = false;
			for (Point known : knownPoints) {
				for (Point unknown : input[scanner]) {
					int diffX = unknown.x - known.x;
					int diffY = unknown.y - known.y;
					int diffZ = unknown.z - known.z;

					for (int rotNum = 0; rotNum < 24; rotNum++) {
						convertedPoints.clear();
						for (Point toConvert : input[scanner]) {
							Point convertedPoint = rotations[rotNum]({toConvert.x - diffX, toConvert.y - diffY, toConvert.z - diffZ});
							convertedPoints.push_back(convertedPoint);
						}
						std::sort(convertedPoints.begin(), convertedPoints.end());

						std::vector<Point> intersection = {{0, 0, 0}};
						std::set_intersection(knownPoints.begin(), knownPoints.end(), convertedPoints.begin(), convertedPoints.end(), std::back_inserter(intersection));
						if (intersection.size() >= 12) {
							knownPoints.insert(knownPoints.end(), convertedPoints.begin(), convertedPoints.end());
							std::sort(knownPoints.begin(), knownPoints.end());
							knownPoints.erase(std::unique(knownPoints.begin(), knownPoints.end()), knownPoints.end());
							input.erase(input.begin() + scanner);
							found = true;
							break;
						}
					}
					if (found)
						break;
				}
				if (found)
					break;
			}
		}
	}
	printf("Part 1: %zu\n", knownPoints.size());

	return 0;
}