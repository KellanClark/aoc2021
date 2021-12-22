
#include <ios>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>

int rolls = 0;
int rollDie() {
	static int lastNum = 1;

	if (lastNum > 100)
		lastNum = 1;

	++rolls;
	return lastNum++;
}

int main() {
	std::fstream inFile{"../day21/input", std::ios::in};

	// x = p1Score y = p2Score z = p1Position a = p2Position
	unsigned long long universes[31][31][10][10];
	unsigned long long nextStep[31][31][10][10];
	memset(universes, 0, sizeof(universes));

	int p1Position, p2Position;
	inFile.ignore(28);
	inFile >> p1Position;
	inFile.ignore(28);
	inFile >> p2Position;
	universes[0][0][p1Position - 1][p2Position - 1] = 1;

	// Part 1
	int p1Score = 0;
	int p2Score = 0;
	while (1) {
		p1Position = (((p1Position - 1) + rollDie() + rollDie() + rollDie()) % 10) + 1;
		p1Score += p1Position;
		if (p1Score >= 1000)
			break;

		p2Position = (((p2Position - 1) + rollDie() + rollDie() + rollDie()) % 10) + 1;
		p2Score += p2Position;
		if (p2Score >= 1000)
			break;
	}
	printf("Part 1: %d\n", ((p1Score >= 1000) ? p2Score : p1Score) * rolls);

	// Part 2
	bool p1Turn = true;
	for (int i = 0; i < 22; i++) {
		memcpy(nextStep, universes, sizeof(universes));
		for (int p1Score = 0; p1Score < 21; p1Score++) {
			for (int p2Score = 0; p2Score < 21; p2Score++) {
				for (int p1Position = 0; p1Position < 10; p1Position++) {
					for (int p2Position = 0; p2Position < 10; p2Position++) {
						unsigned long long count = universes[p1Score][p2Score][p1Position][p2Position];

						nextStep[p1Score][p2Score][p1Position][p2Position] -= count;
						if (p1Turn) {
							nextStep[p1Score + ((p1Position + 3) % 10) + 1][p2Score][(p1Position + 3) % 10][p2Position] += count * 1;
							nextStep[p1Score + ((p1Position + 4) % 10) + 1][p2Score][(p1Position + 4) % 10][p2Position] += count * 3;
							nextStep[p1Score + ((p1Position + 5) % 10) + 1][p2Score][(p1Position + 5) % 10][p2Position] += count * 6;
							nextStep[p1Score + ((p1Position + 6) % 10) + 1][p2Score][(p1Position + 6) % 10][p2Position] += count * 7;
							nextStep[p1Score + ((p1Position + 7) % 10) + 1][p2Score][(p1Position + 7) % 10][p2Position] += count * 6;
							nextStep[p1Score + ((p1Position + 8) % 10) + 1][p2Score][(p1Position + 8) % 10][p2Position] += count * 3;
							nextStep[p1Score + ((p1Position + 9) % 10) + 1][p2Score][(p1Position + 9) % 10][p2Position] += count * 1;
						} else {
							nextStep[p1Score][p2Score + ((p2Position + 3) % 10) + 1][p1Position][(p2Position + 3) % 10] += count * 1;
							nextStep[p1Score][p2Score + ((p2Position + 4) % 10) + 1][p1Position][(p2Position + 4) % 10] += count * 3;
							nextStep[p1Score][p2Score + ((p2Position + 5) % 10) + 1][p1Position][(p2Position + 5) % 10] += count * 6;
							nextStep[p1Score][p2Score + ((p2Position + 6) % 10) + 1][p1Position][(p2Position + 6) % 10] += count * 7;
							nextStep[p1Score][p2Score + ((p2Position + 7) % 10) + 1][p1Position][(p2Position + 7) % 10] += count * 6;
							nextStep[p1Score][p2Score + ((p2Position + 8) % 10) + 1][p1Position][(p2Position + 8) % 10] += count * 3;
							nextStep[p1Score][p2Score + ((p2Position + 9) % 10) + 1][p1Position][(p2Position + 9) % 10] += count * 1;
						}
					}
				}
			}
		}
		memcpy(universes, nextStep, sizeof(nextStep));
		p1Turn = !p1Turn;
	}
	unsigned long long p1Wins = 0;
	unsigned long long p2Wins = 0;
	for (int p1Score = 0; p1Score < 31; p1Score++) {
		for (int p2Score = 0; p2Score < 31; p2Score++) {
			for (int p1Position = 0; p1Position < 10; p1Position++) {
				for (int p2Position = 0; p2Position < 10; p2Position++) {
					unsigned long long count = universes[p1Score][p2Score][p1Position][p2Position];
					if ((p1Score >= 21) && count) {
						p1Wins += count;
					} else if ((p2Score >= 21) && count) {
						p2Wins += count;
					}
				}
			}
		}
	}
	printf("Part 2: %llu\n", (p1Wins > p2Wins) ? p1Wins : p2Wins);
}

/*
                                  0
          1                       2                       3
  2       3       4       3       4       5       4       5       6
3 4 5   4 5 6   5 6 7   4 5 6   5 6 7   6 7 8   5 6 7   6 7 8   7 8 9

3: 1
4: 3
5: 6
6: 7
7: 6
8: 3
9: 1
Total: 27
*/