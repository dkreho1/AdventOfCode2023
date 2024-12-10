#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <utility>
#include <set>


#define MY_INPUT_PATH R"(..\inputDay21.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day21.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day21.txt)"


std::pair<int, int> operator+(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    return { p1.first + p2.first, p1.second + p2.second };
}


long long solutionPart1(const char* inputPath, const int numOfSteps) {
    std::ifstream input(inputPath);

    std::vector<std::string> gardenMap;
    std::set<std::pair<int, int>> gardenPlots;

    for (std::string line; std::getline(input, line); gardenMap.push_back(line)) {
        if (std::size_t start{ line.find('S') }; start != std::string::npos) {
            gardenPlots.emplace(gardenMap.size(), start);
        }
    }

    std::size_t gardenWidth{ gardenMap.front().length() },
        gardenHeight{ gardenMap.size() };
    auto isValidGardenPlot{
        [gardenWidth, gardenHeight](const std::pair<int, int>& gardenPlot) {
            return gardenPlot.first >= 0 && gardenPlot.first < gardenHeight &&
                   gardenPlot.second >= 0 && gardenPlot.second < gardenWidth;
        }
    };

    for (int i{}; i < numOfSteps; ++i) {
        std::set<std::pair<int, int>> newGardenPlots;
        for (auto&& gardenPlot : gardenPlots) {
            for (auto plotIncr
                : { std::make_pair(0, 1), std::make_pair(0, -1),
                    std::make_pair(1, 0), std::make_pair(-1, 0) }
            ) {
                if (
                    auto newPlot{ gardenPlot + plotIncr };
                    isValidGardenPlot(newPlot)
                    && gardenMap.at(newPlot.first).at(newPlot.second) != '#'
                ) {
                    newGardenPlots.insert(newPlot);
                }
            }
        }

        gardenPlots = newGardenPlots;
    }

    return gardenPlots.size();
}


long long solutionPart2(const char* inputPath, const int numOfSteps) {
    std::ifstream input(inputPath);

    std::vector<std::string> gardenMap;
    std::set<std::pair<int, int>> gardenPlots;

    for (std::string line; std::getline(input, line); gardenMap.push_back(line)) {
        if (std::size_t start{ line.find('S') }; start != std::string::npos) {
            gardenPlots.emplace(gardenMap.size(), start);
        }
    }

    int gardenWidth{ static_cast<int>(gardenMap.front().length()) },
            gardenHeight{ static_cast<int>(gardenMap.size()) };

    auto infiniteMap {
        [gardenMap, gardenWidth, gardenHeight](int x, int y) -> char {
            x %= gardenHeight;
            if (x < 0) {
                x += gardenHeight;
            }

            y %= gardenWidth;
            if (y < 0) {
                y += gardenWidth;
            }

            return gardenMap.at(x).at(y);
        }
    };

    for (int i{}; i < numOfSteps; ++i) {
        std::set<std::pair<int, int>> newGardenPlots;
        for (auto&& gardenPlot : gardenPlots) {
            for (auto plotIncr
                : { std::make_pair(0, 1), std::make_pair(0, -1),
                std::make_pair(1, 0), std::make_pair(-1, 0) }
            ) {
                if (
                    auto newPlot{ gardenPlot + plotIncr };
                    infiniteMap(newPlot.first, newPlot.second) != '#'
                ) {
                    newGardenPlots.insert(newPlot);
                }
            }
        }

        gardenPlots = newGardenPlots;
    }

    return gardenPlots.size();
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
    std::cout << "\tPart 1: " << solutionPart1(TEST_INPUT_PART1_PATH, 6) << std::endl;
    std::cout << "\tPart 2: " << solutionPart2(TEST_INPUT_PART2_PATH, 50) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(MY_INPUT_PATH, 64) << std::endl;
//    std::cout << "\tPart 2: " << solutionPart2(MY_INPUT_PATH) << std::endl;
    std::cout << "My input runtime [ms]:" << std::endl;
    std::cout << "\tPart 1: " << measureTime([](){ solutionPart1(MY_INPUT_PATH, 64); }, 1000) << std::endl;
//    std::cout << "\tPart 2: " << measureTime([](){ solutionPart2(MY_INPUT_PATH); }, 1000) << std::endl;

    return 0;
}
