#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
#include <algorithm>
#include <ios>


#define MY_INPUT_PATH R"(..\inputDay18.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day18.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day18.txt)"


struct BoundaryPoint {
    long long x;
    long long y;

    bool operator== (const BoundaryPoint&) const = default;

    BoundaryPoint move(char direction, long long numOfSteps) {
        switch (direction) {
            case 'U':
                return { x - numOfSteps, y };
            case 'D':
                return { x + numOfSteps, y };
            case 'L':
                return { x, y - numOfSteps };
            case 'R':
                return { x, y + numOfSteps };
            default:
                break;
        }

        return *this;
    };

    long long manhattanDistance(const BoundaryPoint& point) const {
        return std::abs(x - point.x) + std::abs(y - point.y);
    }
};


long long solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    std::vector<std::tuple<char, long long>> digPlan;
    for (std::string line; std::getline(input, line); ) {
        std::stringstream ss(line);
        char direction;
        int numOfSteps;

        ss >> direction >> numOfSteps;

        digPlan.emplace_back(direction, numOfSteps);
    }

    BoundaryPoint start{0, 0};
    std::vector<BoundaryPoint> boundaryPoints{ start };
    long long totalNumOfBoundaryPoints{};

    for (const auto& digStep : digPlan) {
        BoundaryPoint newBoundaryPoint{
            boundaryPoints.back().move(
                std::get<0>(digStep),
                std::get<1>(digStep)
            )
        };

        totalNumOfBoundaryPoints +=
                boundaryPoints.back().manhattanDistance(newBoundaryPoint);

        boundaryPoints.push_back(newBoundaryPoint);
    }

    if (boundaryPoints.back() != start) {
        return -1;
    }
    boundaryPoints.erase(boundaryPoints.end() - 1);

    long long trenchArea{};
    BoundaryPoint current{}, previous{ boundaryPoints.at(0) };
    for (int i{ 1 }; i < boundaryPoints.size(); ++i, previous = current) {
        current = boundaryPoints.at(i);
        trenchArea += (current.x - previous.x) * (current.y + previous.y);
    }

    return (std::abs(trenchArea) + totalNumOfBoundaryPoints) / 2 + 1;
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    const char* directions{ "RDLU" };
    std::vector<std::tuple<char, long long>> digPlan;
    for (std::string line; std::getline(input, line); ) {
        std::stringstream ss(line);
        char direction;
        int numOfSteps;
        std::string colorCode;

        ss >> direction >> numOfSteps >> colorCode;

        (std::stringstream() << std::hex << colorCode.substr(2, 5)) >> numOfSteps;
        direction = directions[*(colorCode.end() - 2) - '0'];

        digPlan.emplace_back(direction, numOfSteps);
    }

    BoundaryPoint start{0, 0};
    std::vector<BoundaryPoint> boundaryPoints{ start };
    long long totalNumOfBoundaryPoints{};

    for (const auto& digStep : digPlan) {
        BoundaryPoint newBoundaryPoint{
                boundaryPoints.back().move(
                        std::get<0>(digStep),
                        std::get<1>(digStep)
                )
        };

        totalNumOfBoundaryPoints +=
                boundaryPoints.back().manhattanDistance(newBoundaryPoint);

        boundaryPoints.push_back(newBoundaryPoint);
    }

    if (boundaryPoints.back() != start) {
        return -1;
    }
    boundaryPoints.erase(boundaryPoints.end() - 1);

    long long trenchArea{};
    BoundaryPoint current{}, previous{ boundaryPoints.at(0) };
    for (int i{ 1 }; i < boundaryPoints.size(); ++i, previous = current) {
        current = boundaryPoints.at(i);
        trenchArea += (current.x - previous.x) * (current.y + previous.y);
    }

    return (std::abs(trenchArea) + totalNumOfBoundaryPoints) / 2 + 1;
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