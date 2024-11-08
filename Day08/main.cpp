#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <numeric>


#define MY_INPUT_PATH R"(..\inputDay8.txt)"
#define TEST_INPUT1_PART1_PATH R"(..\testInput1Part1Day8.txt)"
#define TEST_INPUT2_PART1_PATH R"(..\testInput2Part1Day8.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day8.txt)"


long long solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    std::string leftRightInstr;
    input >> leftRightInstr;

    std::map<std::string, std::map<char, std::string>> nodes;

    for (std::string line; std::getline(input, line); ) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string node, dummyString, left, right;
        ss >> node >> dummyString >> left >> right;

        right.erase(right.end() - 1);
        left.erase(left.end() - 1);
        left.erase(left.begin());

        nodes[node] = {{'L', left}, {'R', right}};
    }

    long long numOfSteps{};
    std::string currentNode{ "AAA" };
    for (std::string::iterator it{leftRightInstr.begin()}; currentNode != "ZZZ"; ++numOfSteps) {
        currentNode = nodes[currentNode][*it];

        if (++it == leftRightInstr.end()) {
            it = leftRightInstr.begin();
        }
    }

    return numOfSteps;
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    std::string leftRightInstr;
    input >> leftRightInstr;

    std::map<std::string, std::map<char, std::string>> nodes;
    std::vector<std::string> startNodes;

    for (std::string line; std::getline(input, line); ) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string node, dummyString, left, right;
        ss >> node >> dummyString >> left >> right;

        right.erase(right.end() - 1);
        left.erase(left.end() - 1);
        left.erase(left.begin());

        nodes[node] = {{'L', left}, {'R', right}};

        if (*(node.end() - 1) == 'A') {
            startNodes.push_back(node);
        }
    }

    std::vector<long long> numOfSteps(startNodes.size(), 0);
    for (int i{}; i < startNodes.size(); ++i) {
        std::string currentNode{ startNodes.at(i) };
        for (std::string::iterator it{leftRightInstr.begin()}; *(currentNode.end() - 1) != 'Z'; ++numOfSteps.at(i)) {
            currentNode = nodes[currentNode][*it];

            if (++it == leftRightInstr.end()) {
                it = leftRightInstr.begin();
            }
        }
    }

    long long totalNumberOfSteps{ 1 };

    for (auto&& n : numOfSteps) {
        totalNumberOfSteps = std::lcm(totalNumberOfSteps, n);
    }

    return totalNumberOfSteps;
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
    std::cout << "\tInput 1 Part 1: " << solutionPart1(TEST_INPUT1_PART1_PATH) << std::endl;
    std::cout << "\tInput 2 Part 1: " << solutionPart1(TEST_INPUT2_PART1_PATH) << std::endl;
    std::cout << "\tPart 2: " << solutionPart2(TEST_INPUT_PART2_PATH) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(MY_INPUT_PATH) << std::endl;
    std::cout << "\tPart 2: " << solutionPart2(MY_INPUT_PATH) << std::endl;
    std::cout << "My input runtime [ms]:" << std::endl;
    std::cout << "\tPart 1: " << measureTime([](){ solutionPart1(MY_INPUT_PATH); }, 1000) << std::endl;
    std::cout << "\tPart 2: " << measureTime([](){ solutionPart2(MY_INPUT_PATH); }, 1000) << std::endl;

    return 0;
}
