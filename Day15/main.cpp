#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>


#define MY_INPUT_PATH R"(..\inputDay15.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day15.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day15.txt)"


long long  solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    long long sumOfValues{};
    while (!input.eof()) {
        std::string currentStep;
        for (char c{}; input >> c && c != ','; currentStep += c);

        long long currentValue{};
        for (auto&& c : currentStep) {
            ((currentValue += c) *= 17) %= 256;
        }
        sumOfValues += currentValue;
    }

    return sumOfValues;
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    long long sumOfFocusingPowers{};
    std::vector<std::vector< std::pair<std::string, int>>> boxes(256);

    while (!input.eof()) {
        std::string currentStep;
        for (char c{}; input >> c && c != ','; currentStep += c);

        if (*(currentStep.end() - 1) == '-') {
            currentStep.erase(currentStep.end() - 1);

            long long boxNum{};
            for (auto&& c : currentStep) {
                ((boxNum += c) *= 17) %= 256;
            }

            boxes.at(boxNum).erase(
                    std::remove_if(boxes.at(boxNum).begin(), boxes.at(boxNum).end(),
                           [currentStep] (const std::pair<std::string, int>& lens) {
                                return currentStep == lens.first;
                           }
                    ),
                    boxes.at(boxNum).end()
            );
        } else {
            auto equalsPos{ currentStep.find('=') };
            std::string boxStr{ currentStep.substr(0, equalsPos) };

            long long boxNum{};
            for (auto&& c : boxStr) {
                ((boxNum += c) *= 17) %= 256;
            }

            auto found{
                std::find_if(boxes.at(boxNum).begin(), boxes.at(boxNum).end(),
                             [boxStr](const std::pair<std::string, int>& lens) {
                    return boxStr == lens.first;
                })
            };

            if (found == boxes.at(boxNum).end()) {
                boxes.at(boxNum).emplace_back(boxStr, std::stoi(currentStep.substr(equalsPos + 1)));
            } else {
                found->second = std::stoi(currentStep.substr(equalsPos + 1));
            }
        }
    }

    for (int i{}; i < boxes.size(); ++i) {
        for (int j{}; j < boxes.at(i).size(); ++j) {
            sumOfFocusingPowers += (i + 1) * (j + 1) * boxes.at(i).at(j).second;
        }
    }

    return sumOfFocusingPowers;
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
