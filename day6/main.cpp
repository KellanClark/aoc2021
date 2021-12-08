
#include <stdio.h>
#include <fstream>
#include <vector>

int main () {
    std::fstream inFile("../day6/input", std::ios_base::in);

    long unsigned int ages[9] = {0};
    long unsigned int total = 0;
    int readValue = 0;
    while (inFile >> readValue) {
        inFile.ignore(1);

        ++ages[readValue];
        ++total;
    }

    // Part 1/2
    for (int i = 0; i < 256; i++) {
        if (i == 80)
            printf("Part 1: %zu\n", total);

        long unsigned int newCount = ages[0];
        for (int j = 1; j < 9; j++)
            ages[j - 1] = ages[j];
        ages[6] += newCount;
        ages[8] = newCount;
        total += newCount;
    }
    printf("Part 2: %zu\n", total);

    return 0;
}