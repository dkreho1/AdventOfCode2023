#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <vector>


#define MY_INPUT_PATH R"(..\inputDay13.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day13.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day13.txt)"


int solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    int summarizePatterns{};
    std::vector<std::string> currentPattern;
    for (std::string line; std::getline(input, line); ) {
        if (!line.empty()) {
            currentPattern.push_back(line);
            if (!input.eof()) {
                continue;
            }
        }

        for (int i{}; i + 1 < currentPattern.size(); ++i) {
            auto up{ i }, down{ i + 1 };
            bool matching{ true };
            while (up >= 0 && down < currentPattern.size()) {
                matching = currentPattern.at(up) == currentPattern.at(down);

                if (!matching) {
                    break;
                }

                --up;
                ++down;
            }

            if (matching && (up == -1 || down == currentPattern.size())) {
                summarizePatterns += (i + 1) * 100;
                break;
            }
        }

        for (int j{}; j + 1 < currentPattern.at(0).size(); ++j) {
            auto left{ j }, right{ j + 1 };
            bool matching{ true };
            while (left >= 0 && right < currentPattern.at(0).size()) {
                for (int i{}; i < currentPattern.size(); ++i) {
                    matching = currentPattern.at(i).at(left) == currentPattern.at(i).at(right);
                    if (!matching) {
                        break;
                    }
                }

                if (!matching) {
                    break;
                }

                --left;
                ++right;
            }

            if (matching && (left == -1 || right == currentPattern.at(0).size())) {
                summarizePatterns += (j + 1);
                break;
            }
        }

        currentPattern.clear();
    }

    return summarizePatterns;
}


int solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    int summarizePatterns{};
    std::vector<std::string> currentPattern;
    for (std::string line; std::getline(input, line); ) {
        if (!line.empty()) {
            currentPattern.push_back(line);
            if (!input.eof()) {
                continue;
            }
        }

        for (int i{}; i + 1 < currentPattern.size(); ++i) {
            auto up{ i }, down{ i + 1 };
            bool matching{ true }, secondChange{ true };

            while (up >= 0 && down < currentPattern.size()) {
                for (int j{}; j < currentPattern.at(0).size(); ++j) {
                    matching = currentPattern.at(up).at(j) == currentPattern.at(down).at(j);

                    if (!matching) {
                        if (!secondChange) {
                            break;
                        }

                        matching = true;
                        secondChange = false;
                    }
                }

                if (!matching && !secondChange) {
                    break;
                }

                --up;
                ++down;
            }

            if (matching && !secondChange && (up == -1 || down == currentPattern.size())) {
                summarizePatterns += (i + 1) * 100;
                break;
            }
        }

        for (int j{}; j + 1 < currentPattern.at(0).size(); ++j) {
            auto left{ j }, right{ j + 1 };
            bool matching{ true }, secondChange{ true };

            while (left >= 0 && right < currentPattern.at(0).size()) {
                for (int i{}; i < currentPattern.size(); ++i) {
                    matching = currentPattern.at(i).at(left) == currentPattern.at(i).at(right);

                    if (!matching) {
                        if (!secondChange) {
                            break;
                        }

                        matching = true;
                        secondChange = false;
                    }
                }

                if (!matching && !secondChange) {
                    break;
                }

                --left;
                ++right;
            }

            if (matching && !secondChange && (left == -1 || right == currentPattern.at(0).size())) {
                summarizePatterns += (j + 1);
                break;
            }
        }

        currentPattern.clear();
    }

    return summarizePatterns;
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
