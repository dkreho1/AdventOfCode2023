#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <functional>
#include <chrono>

#define MY_INPUT_PATH R"(..\inputDay6.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day6.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day6.txt)"


long long solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    std::vector<int> times, distances;
    for (auto&& vec: { &times, &distances }) {
        std::string line;
        std::getline(input, line);

        std::stringstream ss(line);

        std::string garbageTmpStr;
        ss >> garbageTmpStr;

        int num;
        while(ss >> num) {
            vec->push_back(num);
        }

        ss.clear();
    }

    long long numOfWaysToWin{ 1 };
    for (int i = 0; i < times.size(); ++i) {
        long long firstWin{};
        while ((times.at(i) - firstWin) * firstWin <= distances.at(i)) {
            firstWin++;
        }

        long long lastWin{times.at(i)};
        while ((times.at(i) - lastWin) * lastWin <= distances.at(i)) {
            lastWin--;
        }

        numOfWaysToWin *= lastWin - firstWin + 1;
    }

    return numOfWaysToWin;
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    long long time{}, distance{};
    for (auto&& var: { &time, &distance }) {
        std::string line;
        std::getline(input, line);

        std::stringstream ss(line);

        std::string garbageTmpStr;
        ss >> garbageTmpStr;

        std::string num;
        std::getline(ss, num);
        num.erase(remove_if(num.begin(), num.end(), isspace), num.end());

        *var = std::stoll(num);

        ss.clear();
    }

    long long firstWin{};
    while ((time - firstWin) * firstWin <= distance) {
        firstWin++;
    }

    long long lastWin{time};
    while ((time - lastWin) * lastWin <= distance) {
        lastWin--;
    }

    return lastWin - firstWin + 1;
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
