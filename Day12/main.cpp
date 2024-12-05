#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <utility>


#define MY_INPUT_PATH R"(..\inputDay12.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day12.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day12.txt)"


long long countPossibleArrangements(
        const std::string& springs,
        const std::vector<int>& contiguousDamagedSprings
) {
    static std::map<std::pair<std::string, std::vector<int>>, long long> cache;

    auto currentInput{ std::make_pair(springs, contiguousDamagedSprings) };

    if (cache.contains(currentInput)) {
        return cache.at(currentInput);
    }

    if (contiguousDamagedSprings.empty() && (springs.empty() || springs.find('#') == std::string::npos)) {
        return cache[currentInput] = 1;
    }

    if ((!contiguousDamagedSprings.empty() && springs.empty()) ||
        (contiguousDamagedSprings.empty() && springs.find('#') != std::string::npos)) {
        return cache[currentInput] = 0;
    }

    long long count{};

    if (springs.front() == '.' || springs.front() == '?') {
        count += countPossibleArrangements(springs.substr(1), contiguousDamagedSprings);
    }

    if (springs.front() == '#' || springs.front() == '?') {
        if (contiguousDamagedSprings.front() > springs.length()) {
            return cache[currentInput] = count;
        }

        if (contiguousDamagedSprings.front() == springs.length()) {
            if (springs.find('.') != std::string::npos) {
                return cache[currentInput] = count;
            }

            count += countPossibleArrangements(
                "",
                std::vector<int>(contiguousDamagedSprings.begin() + 1, contiguousDamagedSprings.end())
            );
        }

        if (contiguousDamagedSprings.front() < springs.length()) {
            if (springs.at(contiguousDamagedSprings.front()) == '#') {
                return cache[currentInput] = count;
            }

            if (springs.substr(0, contiguousDamagedSprings.front()).find('.') != std::string::npos) {
                return cache[currentInput] = count;
            }

            count += countPossibleArrangements(
                springs.substr(contiguousDamagedSprings.front() + 1),
                std::vector<int>(contiguousDamagedSprings.begin() + 1, contiguousDamagedSprings.end())
            );
        }
    }

    return cache[currentInput] = count;
}


long long  solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    long long sumOfArrangements{};

    for (std::string line; std::getline(input, line); ) {
        std::stringstream ss(line);

        std::string springs;
        ss >> springs;

        std::vector<int> contiguousDamagedSprings;
        int num, largestNum{};
        char comma;
        while (ss >> num) {
            if (num > largestNum) {
                largestNum = num;
            }
            contiguousDamagedSprings.push_back(num);
            ss >> comma;
        }

        sumOfArrangements += countPossibleArrangements(springs, contiguousDamagedSprings);
    }

    return sumOfArrangements;
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    long long sumOfArrangements{};

    for (std::string line; std::getline(input, line); ) {
        std::stringstream ss(line);

        std::string springs;
        ss >> springs;

        auto initSprings{springs};
        for (int i{}; i < 4; ++i) {
            springs += '?' + initSprings;
        }

        std::vector<int> contiguousDamagedSprings;
        int num, largestNum{};
        char comma;
        while (ss >> num) {
            if (num > largestNum) {
                largestNum = num;
            }
            contiguousDamagedSprings.push_back(num);
            ss >> comma;
        }

        auto initSize{ contiguousDamagedSprings.size() };
        for (int i{}; i < 4; ++i) {
            for (int j{}; j < initSize; ++j) {
                contiguousDamagedSprings.push_back(contiguousDamagedSprings.at(j));
            }
        }

        sumOfArrangements += countPossibleArrangements(springs, contiguousDamagedSprings);
    }

    return sumOfArrangements;
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
