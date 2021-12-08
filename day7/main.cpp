
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    std::fstream inFile("../day7/input", std::ios_base::in);

    std::vector<int> input;
    int readValue = 0;
    while (inFile >> readValue) {
        inFile.ignore(1);

        input.push_back(readValue);
    }

    // Part 1
    std::nth_element(input.begin(), input.begin() + (input.size() / 2), input.end());
    int targetPos1 = input[input.size() / 2];

    int fuel1 = 0;
    for (int i : input)
        fuel1 += std::abs(targetPos1 - i);
    printf("Part 1: %d\n", fuel1);

    // Part 2
    int targetPos2 = 0;
    for (int i : input)
        targetPos2 += i;
    targetPos2 = targetPos2 / input.size();

    int fuel2 = 0;
    for (int i : input) {
        float x = std::abs(targetPos2 - i);
        fuel2 += (0.5 * (x * x)) + (0.5 * x);
    }
    printf("Part 2: %d\n", fuel2);

    return 0;
}