#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <utility>
#include <cmath>


#define MY_INPUT_PATH R"(..\inputDay11.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day11.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day11.txt)"


long long solution(const char* inputPath, long long expansionFactor) {
    std::ifstream input(inputPath);

    std::vector<std::pair<long long, long long>> galaxies;
    std::vector<std::string> image;
    std::vector<bool> expandedRows, expandedColumns;

    for (std::string line; std::getline(input, line); ) {
        image.push_back(line);

        if (expandedColumns.empty()) {
            expandedColumns.resize(line.length(), true);
        }

        std::size_t found{line.find('#')}, oldFound{};
        expandedRows.push_back(found == std::string::npos);
        while (found = line.find('#'), found != std::string::npos) {
            galaxies.emplace_back(image.size() - 1, found + oldFound);
            expandedColumns.at(found + oldFound) = false;
            oldFound += found + 1;
            line = line.substr(found + 1);
        }
    }

    for (auto&& galaxy : galaxies) {
        long long rowExpansion{};
        for (int i{}; i < expandedRows.size(); ++i) {
            rowExpansion += expandedRows.at(i) && galaxy.first > i;
        }
        galaxy.first += rowExpansion * (expansionFactor - 1);

        long long columnExpansion{};
        for (int i{}; i < expandedColumns.size(); ++i) {
            columnExpansion += expandedColumns.at(i) && galaxy.second > i;
        }
        galaxy.second += columnExpansion * (expansionFactor - 1);
    }

    long long shortestPathsSum{};
    for (int i{}; i < galaxies.size(); ++i) {
        for (int j{i + 1}; j < galaxies.size(); ++j) {
            shortestPathsSum += std::abs(galaxies.at(i).first - galaxies.at(j).first)
                                + std::abs(galaxies.at(i).second - galaxies.at(j).second);
        }
    }

    return shortestPathsSum;
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
    std::cout << "\tPart 1: " << solution(TEST_INPUT_PART1_PATH, 2) << std::endl;
    std::cout << "\tPart 2: " << solution(TEST_INPUT_PART2_PATH, 100) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solution(MY_INPUT_PATH, 2) << std::endl;
    std::cout << "\tPart 2: " << solution(MY_INPUT_PATH, 1000000) << std::endl;
    std::cout << "My input runtime [ms]:" << std::endl;
    std::cout << "\tPart 1: " << measureTime([](){ solution(MY_INPUT_PATH, 2); }, 1000) << std::endl;
    std::cout << "\tPart 2: " << measureTime([](){ solution(MY_INPUT_PATH, 1000000); }, 1000) << std::endl;

    return 0;
}