#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <bitset>
#include <regex>


#define MY_INPUT_PATH R"(..\inputDay12.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day12.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day12.txt)"


long long  solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    long long sumOfArrangements{};

    for (std::string line; std::getline(input, line); ) {
        std::stringstream ss(line);

        std::string springs;
        ss >> springs;

        std::vector<int> contiguousDamagedSprings;
        int num, totalDamagedSprings{};
        char comma;
        while (ss >> num) {
            totalDamagedSprings += num;
            contiguousDamagedSprings.push_back(num);
            ss >> comma;
        }

        auto checkGroups =
                [] (std::string springs, const std::vector<int>& groups) -> bool {
                    std::regex exp(std::string(R"(\#+)"));
                    std::smatch sm;

                    int i{};
                    for (; std::regex_search(springs, sm, exp); ++i) {
                        if (i == groups.size() || sm.str().length() != groups.at(i)) {
                            return false;
                        }

                        springs = sm.suffix().str();
                    }

            return i == groups.size();
        };

        std::vector<int> unknowns;
        for (int i{}; i < springs.length(); ++i) {
            totalDamagedSprings -= springs.at(i) == '#';
            if (springs.at(i) == '?') {
                unknowns.push_back(i);
            }
        }

        int numOfVariations{ static_cast<int>(std::pow(2, unknowns.size())) };
        for (int i{}, totalTmp{}; i < numOfVariations; ++i) {
            totalTmp = totalDamagedSprings;
            std::string variation{ springs };

            for (int j{}, iTmp{i}; j < unknowns.size(); ++j) {
                totalTmp -= iTmp % 2 == 0;
                variation.at(unknowns.at(j)) = ((iTmp % 2) ? ('.') : ('#'));
                iTmp /= 2;
            }

            if (totalTmp == 0) {
                sumOfArrangements += checkGroups(variation, contiguousDamagedSprings);
            }
        }
    }

    return sumOfArrangements;
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    return 0;
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
//    std::cout << "\tPart 2: " << solutionPart2(TEST_INPUT_PART2_PATH) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(MY_INPUT_PATH) << std::endl;
//    std::cout << "\tPart 2: " << solutionPart2(MY_INPUT_PATH) << std::endl;
    std::cout << "My input runtime [ms]:" << std::endl;
    std::cout << "\tPart 1: " << measureTime([](){ solutionPart1(MY_INPUT_PATH); }, 1) << std::endl;
//    std::cout << "\tPart 2: " << measureTime([](){ solutionPart2(MY_INPUT_PATH); }, 1000) << std::endl;

    return 0;
}
