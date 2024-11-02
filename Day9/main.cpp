#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <sstream>
#include <vector>


#define MY_INPUT_PATH R"(..\inputDay9.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day9.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day9.txt)"


long long solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    long long predictionSum{};

    for (std::string line; std::getline(input, line); ) {
        std::stringstream ss(line);

        std::vector<int> history;
        int num;
        while (ss >> num) {
            history.push_back(num);
        }

        std::vector<int> lastNums;
        while (true) {
            int allZero{};

            lastNums.push_back(*(history.end() - 1));

            for (int i{ 1 }; i < history.size(); ++i) {
                history.at(i - 1) = history.at(i) - history.at(i - 1);
                allZero += history.at(i - 1) == 0;
            }

            history.resize(history.size() - 1);

            if (allZero == history.size()) {
                break;
            }
        }

        long long prediction{};
        for (auto it{lastNums.rbegin()}; it != lastNums.rend(); ++it) {
            prediction += *it;
        }

        predictionSum += prediction;
    }

    return predictionSum;
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    long long predictionSum{};

    for (std::string line; std::getline(input, line); ) {
        std::stringstream ss(line);

        std::vector<int> history;
        int num;
        while (ss >> num) {
            history.push_back(num);
        }

        std::vector<int> firstNums;
        while (true) {
            int allZero{};

            firstNums.push_back(*history.begin());

            for (int i{ 1 }; i < history.size(); ++i) {
                history.at(i - 1) = history.at(i) - history.at(i - 1);
                allZero += history.at(i - 1) == 0;
            }

            history.resize(history.size() - 1);

            if (allZero == history.size()) {
                break;
            }
        }

        long long prediction{};
        for (auto it{firstNums.rbegin()}; it != firstNums.rend(); ++it) {
            prediction = *it - prediction;
        }

        predictionSum += prediction;
    }

    return predictionSum;
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
