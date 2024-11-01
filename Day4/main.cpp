#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>


#define MY_INPUT_PATH R"(..\inputDay4.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day4.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day4.txt)"


int solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    int totalPoints{};

    for (std::string line; std::getline(input, line); ) {
        std::set<int> winningNumbers;

        std::stringstream ss(line);
        std::string garbageTmpStr;
        ss >> garbageTmpStr >> garbageTmpStr;

        int num;

        while (ss >> num) {
            winningNumbers.insert(num);
        }

        ss.clear();
        ss >> garbageTmpStr;

        int winningNumHits{};
        while (ss >> num) {
            winningNumHits += winningNumbers.contains(num);
        }

        if (winningNumHits != 0) {
            totalPoints += 1 << (winningNumHits - 1);
        }
    }

    return totalPoints;
}


int solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    constexpr int maxCardNumber{ 300 };
    int numOfCards[maxCardNumber] = { 0 };
    int totalNumOfCards{};

    for (std::string line; std::getline(input, line); ) {
        std::set<int> winningNumbers, myNumbers;

        std::stringstream ss(line);
        std::string garbageTmpStr;
        int cardNumber;
        ss >> garbageTmpStr >> cardNumber >> garbageTmpStr;

        int num;

        while (ss >> num) {
            winningNumbers.insert(num);
        }

        ss.clear();
        ss >> garbageTmpStr;

        int winningNumHits{};
        while (ss >> num) {
            winningNumHits += winningNumbers.contains(num);
        }

        numOfCards[cardNumber]++;
        totalNumOfCards += numOfCards[cardNumber];

        for (int i = cardNumber + 1; i <= cardNumber + winningNumHits; ++i) {
            numOfCards[i] += numOfCards[cardNumber];
        }
    }

    return totalNumOfCards;
}


int main() {
    std::cout << "Test inputs:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(TEST_INPUT_PART1_PATH) << std::endl;
    std::cout << "\tPart 2: " << solutionPart2(TEST_INPUT_PART2_PATH) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(MY_INPUT_PATH) << std::endl;
    std::cout << "\tPart 2: " << solutionPart2(MY_INPUT_PATH) << std::endl;

    return 0;
}
