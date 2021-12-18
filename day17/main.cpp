
#include <stdio.h>
#include <fstream>
#include <algorithm>

int main() {
	std::fstream inFile{"../day17/input", std::ios::in};

	int targetX, targetMaxX, targetY, targetMaxY;
	inFile.ignore(15);
	inFile >> targetX;
	inFile.ignore(2);
	inFile >> targetMaxX;
	inFile.ignore(4);
	inFile >> targetY;
	inFile.ignore(2);
	inFile >> targetMaxY;

	// Part 1/2
	int maxY = 0;
	int totalVelocities = 0;
	for (int startVelY = -500; startVelY <= 500; startVelY++) {
		for (int startVelX = 0; startVelX <= 500; startVelX++) {
			int x = 0;
			int y = 0;
			int velX = startVelX;
			int velY = startVelY;

			int currMaxY = 0;
			while (1) {
				x += velX;
				y += velY;
				velX -= velX ? std::clamp(velX, -1, 1) : 0;
				velY -= 1;

				if (y > currMaxY)
					currMaxY = y;

				if ((x > targetMaxX) || (y < targetY))
					break;

				if ((x >= targetX) && (x <= targetMaxX) && (y >= targetY) && (y <= targetMaxY)) {
					if (currMaxY > maxY)
						maxY = currMaxY;
					++totalVelocities;
					break;
				}
			}
		}
	}
	printf("Part 1: %d\n", maxY);
	printf("Part 2: %d\n", totalVelocities);

	return 0;
}
