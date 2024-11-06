#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>


#define MY_INPUT_PATH R"(..\inputDay14.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day14.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day14.txt)"


int solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    std::vector<std::string> platform;
    for (std::string line; std::getline(input, line); platform.push_back(line));

    int totalNorthLoad{};
    for (int j{}; j < platform.at(0).size(); ++j) {
        int lastImmovablePos{ -1 };

        if (platform.at(0).at(j) == '#') {
            lastImmovablePos = 0;
        }

        if (platform.at(0).at(j) == 'O') {
            totalNorthLoad += platform.size();
            lastImmovablePos = 0;
        }

        for (int i{ 1 }; i < platform.size(); ++i) {
            if (platform.at(i).at(j) == '#') {
                lastImmovablePos = i;
            } else if (platform.at(i).at(j) == 'O') {
                ++lastImmovablePos;
                totalNorthLoad += platform.size() - lastImmovablePos;
            }
        }
    }

    return totalNorthLoad;
}


int solutionPart2(const char* inputPath) {
    int numOfCycles{1000000000};

    std::ifstream input(inputPath);

    std::vector<std::string> platform;
    for (std::string line; std::getline(input, line); platform.push_back(line));

    std::vector<std::vector<std::string>> cache{ platform };

    for (int cycle{}; cycle < numOfCycles; ++cycle) {
        for (int j{}; j < platform.at(0).size(); ++j) {
            int lastImmovablePos{ -1 + (platform.at(0).at(j) == '#' || platform.at(0).at(j) == 'O') };

            for (int i{ 1 }; i < platform.size(); ++i) {
                if (platform.at(i).at(j) == '#') {
                    lastImmovablePos = i;
                } else if (platform.at(i).at(j) == 'O') {
                    ++lastImmovablePos;
                    platform.at(i).at(j) = '.';
                    platform.at(lastImmovablePos).at(j) = 'O';
                }
            }
        }

        for (int i{}; i < platform.size(); ++i) {
            int lastImmovablePos{ -1 + (platform.at(i).at(0) == '#' || platform.at(i).at(0) == 'O') };

            for (int j{ 1 }; j < platform.at(0).size(); ++j) {
                if (platform.at(i).at(j) == '#') {
                    lastImmovablePos = j;
                } else if (platform.at(i).at(j) == 'O') {
                    ++lastImmovablePos;
                    platform.at(i).at(j) = '.';
                    platform.at(i).at(lastImmovablePos) = 'O';
                }
            }
        }

        for (int j{}; j < platform.at(0).size(); ++j) {
            int lastImmovablePos{ static_cast<int>(platform.size()
                                                   - ((platform.end() - 1)->at(j) == '#'
                                                   || (platform.end() - 1)->at(j) == 'O')) };

            for (int i{ static_cast<int>(platform.size() - 2) }; i >= 0; --i) {
                if (platform.at(i).at(j) == '#') {
                    lastImmovablePos = i;
                } else if (platform.at(i).at(j) == 'O') {
                    --lastImmovablePos;
                    platform.at(i).at(j) = '.';
                    platform.at(lastImmovablePos).at(j) = 'O';
                }
            }
        }

        for (int i{}; i < platform.size(); ++i) {
            int lastImmovablePos{ static_cast<int>(platform.at(0).size()
                                                   - (*(platform.at(i).end() - 1) == '#'
                                                   || *(platform.at(i).end() - 1) == 'O')) };

            for (int j{ static_cast<int>(platform.at(0).size() - 2) }; j >= 0; --j) {
                if (platform.at(i).at(j) == '#') {
                    lastImmovablePos = j;
                } else if (platform.at(i).at(j) == 'O') {
                    --lastImmovablePos;
                    platform.at(i).at(j) = '.';
                    platform.at(i).at(lastImmovablePos) = 'O';
                }
            }
        }

        if (auto found{ std::find(cache.begin(), cache.end(), platform)};
            found != cache.end()) {
            auto lengthOfRepeatingPart{cache.end() - found};
            auto numOfRepetitionsInRemCycles{
                (numOfCycles - cycle) / lengthOfRepeatingPart
                - ((numOfCycles - cycle) % lengthOfRepeatingPart == 0)
            };
            cycle += lengthOfRepeatingPart * numOfRepetitionsInRemCycles;
            platform = *(found + (numOfCycles - cycle - 1));
            break;
        } else {
            cache.push_back(platform);
        }
    }

    int totalNorthLoad{};
    for (int i{}; i < platform.size(); ++i) {
        totalNorthLoad += std::count(platform.at(i).begin(), platform.at(i).end(), 'O') *
                (platform.size() - i);
    }

    return totalNorthLoad;
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
