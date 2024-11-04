#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <cmath>


#define MY_INPUT_PATH R"(..\inputDay10.txt)"
#define TEST_INPUT1_PART1_PATH R"(..\testInput1Part1Day10.txt)"
#define TEST_INPUT2_PART1_PATH R"(..\testInput2Part1Day10.txt)"
#define TEST_INPUT1_PART2_PATH R"(..\testInput1Part2Day10.txt)"
#define TEST_INPUT2_PART2_PATH R"(..\testInput2Part2Day10.txt)"
#define TEST_INPUT3_PART2_PATH R"(..\testInput3Part2Day10.txt)"


const std::set<char> moveRight({'-', '7', 'J'});
const std::set<char> moveLeft({'-', 'L', 'F'});
const std::set<char> moveUp({'|', '7', 'F'});
const std::set<char> moveDown({'|', 'L', 'J'});
const std::map<char, std::set<char>> possibleDirections{
        {'|', {'u', 'd'}},
        {'-', {'l', 'r'}},
        {'L', {'u', 'r'}},
        {'J', {'u', 'l'}},
        {'7', {'d', 'l'}},
        {'F', {'d', 'r'}},
};


int solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    std::vector<std::string> pipeMap;
    std::pair<int, int> start{-1, -1};
    for (std::string line; std::getline(input, line); ) {
        pipeMap.push_back(line);

        if (start.first == -1 && start.second == -1) {
            if (auto found{line.find('S')}; found != std::string::npos) {
                start.first = pipeMap.size() - 1;
                start.second = found;
            }
        }
    }

    if (start.second > 0 && start.second + 1 < pipeMap.at(start.first).size() &&
        moveLeft.contains(pipeMap.at(start.first).at(start.second - 1)) &&
        moveRight.contains(pipeMap.at(start.first).at(start.second + 1))) {
        pipeMap.at(start.first).at(start.second) = '-';
    } else if (start.first > 0 && start.first + 1 < pipeMap.size() &&
               moveUp.contains(pipeMap.at(start.first - 1).at(start.second)) &&
               moveDown.contains(pipeMap.at(start.first + 1).at(start.second))) {
        pipeMap.at(start.first).at(start.second) = '|';
    } else if (start.first + 1 < pipeMap.size() && start.second + 1 < pipeMap.at(start.first).size() &&
               moveDown.contains(pipeMap.at(start.first + 1).at(start.second)) &&
               moveRight.contains(pipeMap.at(start.first).at(start.second + 1))) {
        pipeMap.at(start.first).at(start.second) = 'F';
    } else if (start.first > 0 && start.second + 1 < pipeMap.at(start.first).size() &&
               moveUp.contains(pipeMap.at(start.first - 1).at(start.second)) &&
               moveRight.contains(pipeMap.at(start.first).at(start.second + 1))) {
        pipeMap.at(start.first).at(start.second) = 'L';
    } else if (start.first > 0 && start.second > 0 &&
               moveUp.contains(pipeMap.at(start.first - 1).at(start.second)) &&
               moveLeft.contains(pipeMap.at(start.first).at(start.second - 1))) {
        pipeMap.at(start.first).at(start.second) = 'J';
    } else if (start.first + 1 < pipeMap.size() && start.second > 0 &&
               moveDown.contains(pipeMap.at(start.first + 1).at(start.second)) &&
               moveLeft.contains(pipeMap.at(start.first).at(start.second - 1))) {
        pipeMap.at(start.first).at(start.second) = '7';
    }

    std::vector<std::vector<bool>> visited(pipeMap.size(), std::vector<bool>(pipeMap.at(0).size(), false));
    int numOfVisited{};

    for (auto current{start}; ; numOfVisited++) {
        visited.at(current.first).at(current.second) = true;

        if (current.second + 1 < pipeMap.at(current.first).size() &&
            possibleDirections.at(pipeMap.at(current.first).at(current.second)).contains('r') &&
            moveRight.contains(pipeMap.at(current.first).at(current.second + 1)) &&
            !visited.at(current.first).at(current.second + 1)) {
            current.second++;
        } else if (current.second > 0 &&
                   possibleDirections.at(pipeMap.at(current.first).at(current.second)).contains('l') &&
                   moveLeft.contains(pipeMap.at(current.first).at(current.second - 1)) &&
                   !visited.at(current.first).at(current.second - 1)) {
            current.second--;
        } else if (current.first > 0 &&
                   possibleDirections.at(pipeMap.at(current.first).at(current.second)).contains('u') &&
                   moveUp.contains(pipeMap.at(current.first - 1).at(current.second)) &&
                   !visited.at(current.first - 1).at(current.second)) {
            current.first--;
        } else if (current.first + 1 < pipeMap.size() &&
                   possibleDirections.at(pipeMap.at(current.first).at(current.second)).contains('d') &&
                   moveDown.contains(pipeMap.at(current.first + 1).at(current.second)) &&
                   !visited.at(current.first + 1).at(current.second)) {
            current.first++;
        } else {
            numOfVisited++;
            break;
        }
    }

    return numOfVisited / 2;
}


int solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    std::vector<std::string> pipeMap;
    std::pair<int, int> start{-1, -1};
    for (std::string line; std::getline(input, line); ) {
        pipeMap.push_back(line);

        if (start.first == -1 && start.second == -1) {
            if (auto found{line.find('S')}; found != std::string::npos) {
                start.first = pipeMap.size() - 1;
                start.second = found;
            }
        }
    }

    if (start.second > 0 && start.second + 1 < pipeMap.at(start.first).size() &&
        moveLeft.contains(pipeMap.at(start.first).at(start.second - 1)) &&
        moveRight.contains(pipeMap.at(start.first).at(start.second + 1))) {
        pipeMap.at(start.first).at(start.second) = '-';
    } else if (start.first > 0 && start.first + 1 < pipeMap.size() &&
               moveUp.contains(pipeMap.at(start.first - 1).at(start.second)) &&
               moveDown.contains(pipeMap.at(start.first + 1).at(start.second))) {
        pipeMap.at(start.first).at(start.second) = '|';
    } else if (start.first + 1 < pipeMap.size() && start.second + 1 < pipeMap.at(start.first).size() &&
               moveDown.contains(pipeMap.at(start.first + 1).at(start.second)) &&
               moveRight.contains(pipeMap.at(start.first).at(start.second + 1))) {
        pipeMap.at(start.first).at(start.second) = 'F';
    } else if (start.first > 0 && start.second + 1 < pipeMap.at(start.first).size() &&
               moveUp.contains(pipeMap.at(start.first - 1).at(start.second)) &&
               moveRight.contains(pipeMap.at(start.first).at(start.second + 1))) {
        pipeMap.at(start.first).at(start.second) = 'L';
    } else if (start.first > 0 && start.second > 0 &&
               moveUp.contains(pipeMap.at(start.first - 1).at(start.second)) &&
               moveLeft.contains(pipeMap.at(start.first).at(start.second - 1))) {
        pipeMap.at(start.first).at(start.second) = 'J';
    } else if (start.first + 1 < pipeMap.size() && start.second > 0 &&
               moveDown.contains(pipeMap.at(start.first + 1).at(start.second)) &&
               moveLeft.contains(pipeMap.at(start.first).at(start.second - 1))) {
        pipeMap.at(start.first).at(start.second) = '7';
    }

    std::vector<std::vector<bool>> visited(pipeMap.size(), std::vector<bool>(pipeMap.at(0).size(), false));
    int numOfVisited{}, areaOfLoop{};

    for (auto current{start}, previous{start}; ; numOfVisited++) {
        if (numOfVisited > 0) {
            areaOfLoop += (current.first + previous.first) * (current.second - previous.second);
        }

        visited.at(current.first).at(current.second) = true;
        previous = current;

        if (current.second + 1 < pipeMap.at(current.first).size() &&
            possibleDirections.at(pipeMap.at(current.first).at(current.second)).contains('r') &&
            moveRight.contains(pipeMap.at(current.first).at(current.second + 1)) &&
            !visited.at(current.first).at(current.second + 1)) {
            current.second++;
        } else if (current.second > 0 &&
                   possibleDirections.at(pipeMap.at(current.first).at(current.second)).contains('l') &&
                   moveLeft.contains(pipeMap.at(current.first).at(current.second - 1)) &&
                   !visited.at(current.first).at(current.second - 1)) {
            current.second--;
        } else if (current.first > 0 &&
                   possibleDirections.at(pipeMap.at(current.first).at(current.second)).contains('u') &&
                   moveUp.contains(pipeMap.at(current.first - 1).at(current.second)) &&
                   !visited.at(current.first - 1).at(current.second)) {
            current.first--;
        } else if (current.first + 1 < pipeMap.size() &&
                   possibleDirections.at(pipeMap.at(current.first).at(current.second)).contains('d') &&
                   moveDown.contains(pipeMap.at(current.first + 1).at(current.second)) &&
                   !visited.at(current.first + 1).at(current.second)) {
            current.first++;
        } else {
            areaOfLoop += (current.first + start.first) * (current.second - start.second);
            numOfVisited++;
            break;
        }
    }

    return (std::abs(areaOfLoop) - numOfVisited) / 2 + 1;
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
    std::cout << "\tInput 1 Part 2: " << solutionPart2(TEST_INPUT1_PART2_PATH) << std::endl;
    std::cout << "\tInput 2 Part 2: " << solutionPart2(TEST_INPUT2_PART2_PATH) << std::endl;
    std::cout << "\tInput 3 Part 2: " << solutionPart2(TEST_INPUT3_PART2_PATH) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(MY_INPUT_PATH) << std::endl;
    std::cout << "\tPart 2: " << solutionPart2(MY_INPUT_PATH) << std::endl;
    std::cout << "My input runtime [ms]:" << std::endl;
    std::cout << "\tPart 1: " << measureTime([](){ solutionPart1(MY_INPUT_PATH); }, 1000) << std::endl;
    std::cout << "\tPart 2: " << measureTime([](){ solutionPart2(MY_INPUT_PATH); }, 1000) << std::endl;

    return 0;
}
