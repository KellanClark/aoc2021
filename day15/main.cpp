
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <queue>

struct Node {
	int risk;
	int totalRisk;
	int x, y;
};

int main() {
	std::fstream inFile{"../day15/input", std::ios::in};

	Node grid1[100][100] = {0};
	Node grid2[500][500] = {0};
	std::string readString;
	for (int i = 0; inFile >> readString; i++) {
		int j = 0;
		for (char n : readString) {
			grid1[i][j] = {n - '0', -1, j, i};

			for (int tileY = 0; tileY < 5; tileY++) {
				for (int tileX = 0; tileX < 5; tileX++) {
					int risk = (n - '0') + tileX + tileY;
					if (risk > 9)
						risk = ((risk - 1) % 9) + 1;

					grid2[(tileY * 100) + i][(tileX * 100) + j] = {risk, -1, (tileX * 100) + j, (tileY * 100) + i};
				}
			}

			++j;
		}
	}

	// Part 1
	std::queue<Node> nodeQueue;
	grid1[0][0].totalRisk = 0;
	nodeQueue.push(grid1[0][0]);
	while (!nodeQueue.empty()) {
		Node currentNode = nodeQueue.front();
		nodeQueue.pop();

		auto tryPosition = [&](int x, int y) {
			if ((x >= 0) && (x < 100) && (y >= 0) && (y < 100)) {
				if ((grid1[y][x].totalRisk == -1) || ((currentNode.totalRisk + grid1[y][x].risk) < grid1[y][x].totalRisk)) {
					grid1[y][x].totalRisk = currentNode.totalRisk + grid1[y][x].risk;
					nodeQueue.push(grid1[y][x]);
				}
			}
		};

		tryPosition(currentNode.x - 1, currentNode.y);
		tryPosition(currentNode.x, currentNode.y + 1);
		tryPosition(currentNode.x + 1, currentNode.y);
		tryPosition(currentNode.x, currentNode.y - 1);
	}
	printf("Part 1: %d\n", grid1[99][99].totalRisk);

	// Part 2
	grid2[0][0].totalRisk = 0;
	nodeQueue.push(grid2[0][0]);
	while (!nodeQueue.empty()) {
		Node currentNode = nodeQueue.front();
		nodeQueue.pop();

		auto tryPosition = [&](int x, int y) {
			if ((x >= 0) && (x < 500) && (y >= 0) && (y < 500)) {
				if ((grid2[y][x].totalRisk == -1) || ((currentNode.totalRisk + grid2[y][x].risk) < grid2[y][x].totalRisk)) {
					grid2[y][x].totalRisk = currentNode.totalRisk + grid2[y][x].risk;
					nodeQueue.push(grid2[y][x]);
				}
			}
		};

		tryPosition(currentNode.x - 1, currentNode.y);
		tryPosition(currentNode.x, currentNode.y + 1);
		tryPosition(currentNode.x + 1, currentNode.y);
		tryPosition(currentNode.x, currentNode.y - 1);
	}
	printf("Part 2: %d\n", grid2[499][499].totalRisk);

	return 0;
}