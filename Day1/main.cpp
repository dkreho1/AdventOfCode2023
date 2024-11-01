#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <map>
#include <functional>
#include <chrono>


#define MY_INPUT_PATH R"(..\inputDay1.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day1.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day1.txt)"


int solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    int cumSum{};

    for (std::string line; std::getline(input, line); ) {
        for (auto&& iter=line.begin(); iter != line.end(); ++iter) {
            if (std::isdigit(*iter)) {
                cumSum += 10 * (*iter - '0');
                break;
            }
        }

        for (auto&& iter=line.rbegin(); iter != line.rend(); ++iter) {
            if (std::isdigit(*iter)) {
                cumSum += (*iter - '0');
                break;
            }
        }
    }

    return cumSum;
}


int solutionPart2(const char* inputPath) {
    std::map<std::string, int> digits {
            {"one", 1},  {"1", 1},
            {"two", 2},  {"2", 2},
            {"three", 3},  {"3", 3},
            {"four", 4},  {"4", 4},
            {"five", 5},  {"5", 5},
            {"six", 6},  {"6", 6},
            {"seven", 7},  {"7", 7},
            {"eight", 8},  {"8", 8},
            {"nine", 9},  {"9", 9},
    };

    std::ifstream input(inputPath);

    int cumSum{};

    for (std::string line; std::getline(input, line); ) {
        std::size_t firstOccurrence = line.length(), lastOccurrence = 0;
        int firstNumber, lastNumber = -1;

        for (auto&& digit: digits) {
            std::size_t found = line.find(digit.first);
            if (found != std::string::npos && found <= firstOccurrence) {
                firstOccurrence = found;
                firstNumber = digit.second;
            }

            found = line.rfind(digit.first);
            if (found != std::string::npos && found >= lastOccurrence) {
                lastOccurrence = found;
                lastNumber = digit.second;
            }
        }

        cumSum += (10 * firstNumber) + lastNumber;
    }

    return cumSum;
}


double measureTime(const std::function<void()>& func, int numOfRuns) {
    auto startTime = std::chrono::steady_clock::now();
    for (int i{}; i < numOfRuns; i++) {
        func();
    }
    auto endTime = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / (double)numOfRuns;
}


int main() {
    std::cout << "Test inputs:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(TEST_INPUT_PART1_PATH) << std::endl;
    std::cout << "\tPart 2: " << solutionPart2(TEST_INPUT_PART2_PATH) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(MY_INPUT_PATH) << std::endl;
    std::cout << "\tPart 2: " << solutionPart2(MY_INPUT_PATH) << std::endl;
    std::cout << "My input runtime [ms]:" << std::endl;
    std::cout << "\tPart 1: " << measureTime([](){ solutionPart1(MY_INPUT_PATH); }, 1000) << std::endl;
    std::cout << "\tPart 2: " << measureTime([](){ solutionPart2(MY_INPUT_PATH); }, 1000) << std::endl;

    return 0;
}
