
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <array>

int main() {
	std::fstream inFile{"../day22/input", std::ios::in};
	std::fstream outFile1{"day22output1.scad", std::ios::out | std::ios::trunc};
	std::fstream outFile2{"day22output2.scad", std::ios::out | std::ios::trunc};

	std::stack<bool> opTypes1, opTypes2; // 0 = union 1 = difference
	std::queue<std::array<int, 6>> boxes1, boxes2;
	std::string op;
	int x, xMax, y, yMax, z, zMax, sizeX, sizeY, sizeZ;
	while (inFile >> op) {
		inFile.ignore(3);
		inFile >> x;
		inFile.ignore(2);
		inFile >> xMax;
		sizeX = (xMax - x) + 1;
		inFile.ignore(3);
		inFile >> y;
		inFile.ignore(2);
		inFile >> yMax;
		sizeY = (yMax - y) + 1;
		inFile.ignore(3);
		inFile >> z;
		inFile.ignore(2);
		inFile >> zMax;
		sizeZ = (zMax - z) + 1;

		if ((x <= 50) && (x >= -50) && (y <= 50) && (y >= -50) && (z <= 50) && (z >= -50)) {
			opTypes1.push(op[1] == 'f');
			boxes1.push({x, y, z, sizeX, sizeY, sizeZ});
		}
		opTypes2.push(op[1] == 'f');
		boxes2.push({x, y, z, sizeX, sizeY, sizeZ});
	}

	// Part 1
	while (!opTypes1.empty()) {
		outFile1 << (opTypes1.top() ? "difference" : "union") << "(){\n";
		opTypes1.pop();
	}
	while(!boxes1.empty()) {
		auto box = boxes1.front();
		boxes1.pop();
		outFile1 << "translate([" << box[0] << "," << box[1] << "," << box[2] << "])cube([" << box[3] << "," << box[4] << "," << box[5] << "]);\n}\n";
	}

	// Part 2
	while (!opTypes2.empty()) {
		outFile2 << (opTypes2.top() ? "difference" : "union") << "(){\n";
		opTypes2.pop();
	}
	while(!boxes2.empty()) {
		auto box = boxes2.front();
		boxes2.pop();
		outFile2 << "translate([" << box[0] << "," << box[1] << "," << box[2] << "])cube([" << box[3] << "," << box[4] << "," << box[5] << "]);\n}\n";
	}

	outFile1.close();
	outFile2.close();
	return 0;
}