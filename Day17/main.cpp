#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <numeric>
#include <tuple>


#define MY_INPUT_PATH R"(..\inputDay17.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day17.txt)"
#define TEST_INPUT1_PART2_PATH R"(..\testInput1Part2Day17.txt)"
#define TEST_INPUT2_PART2_PATH R"(..\testInput2Part2Day17.txt)"


enum class Direction{ left = 0, up = 1, right = 2, down = 3, none = 4 };

Direction getOppositeDirection(const Direction& direction) {
    return Direction((int(direction) + 2) % 4);
}


struct Position {
    int x;
    int y;
    inline static int minX{};
    inline static int minY{};
    inline static int maxX{ std::numeric_limits<int>::max() };
    inline static int maxY{ std::numeric_limits<int>::max() };

    bool isValid() const {
        return x >= minX && x <= maxX && y >= minY && y <= maxY;
    }

    Position operator+ (const Position& position) const {
        return { x + position.x, y + position.y };
    }
};


struct Node {
    Position position;
    Direction direction;
    int numOfStepsInSameDir;
};

template <>
struct std::less<Node> {
    bool operator()(const Node& node1, const Node& node2) const {
        if (node1.position.x != node2.position.x) {
            return node1.position.x < node2.position.x;
        }

        if (node1.position.y != node2.position.y) {
            return node1.position.y < node2.position.y;
        }

        if (node1.direction != node2.direction) {
            return int(node1.direction) < int(node2.direction);
        }

        return node1.numOfStepsInSameDir < node2.numOfStepsInSameDir;
    }
};


struct State {
    Node node;
    int heatLoss;
};

template <>
struct std::greater<State> {
    bool operator()(const State& state1, const State& state2) const {
        return state1.heatLoss > state2.heatLoss;
    }
};


int solution(const char* inputPath, int minNumOfSteps, int maxNumOfSteps) {
    std::ifstream input(inputPath);

    std::vector<std::string> heatLossMap;
    for (std::string line; std::getline(input, line); heatLossMap.push_back(line));

    Position::maxX = heatLossMap.size() - 1;
    Position::maxY = heatLossMap.begin()->size() - 1;

    Position startPosition{ Position::minX, Position::minY },
             endPosition{ Position::maxX, Position::maxY };

    std::priority_queue<State, std::vector<State>, std::greater<State>> unprocessedStates;
    std::map<Node, long long> heatLosses;

    Node startNode{ startPosition, Direction::none, 0 };
    unprocessedStates.emplace(startNode, 0);
    heatLosses[startNode] = 0;

    while (!unprocessedStates.empty()) {
        State currentState{ unprocessedStates.top() };
        unprocessedStates.pop();

        if (currentState.node.position.x == endPosition.x &&
            currentState.node.position.y == endPosition.y &&
            currentState.node.numOfStepsInSameDir >= minNumOfSteps) {

            return currentState.heatLoss;
        }

        std::vector<Node> neighbours;

        for (auto& [direction, incr]
            : { std::make_tuple(Direction::down, Position{ -1, 0 }),
                std::make_tuple(Direction::up, Position{ 1, 0 }),
                std::make_tuple(Direction::left, Position{ 0, -1 }),
                std::make_tuple(Direction::right, Position{ 0, 1 }) }) {

            if (Position newPosition{ currentState.node.position + incr };
                newPosition.isValid() &&
                currentState.node.direction != getOppositeDirection(direction)) {

                if (currentState.node.direction != Direction::none &&
                    currentState.node.direction != direction) {
                    if (currentState.node.numOfStepsInSameDir >= minNumOfSteps) {
                        neighbours.emplace_back(newPosition, direction, 1);
                    }
                } else if (currentState.node.numOfStepsInSameDir < maxNumOfSteps) {
                    neighbours.emplace_back(newPosition, direction, currentState.node.numOfStepsInSameDir + 1);
                }
            }
        }

        for (auto&& neighbour : neighbours) {
            if (long long newHeatLoss{
                    currentState.heatLoss + heatLossMap.at(neighbour.position.x).at(neighbour.position.y) - '0'
                }; !heatLosses.contains(neighbour) || newHeatLoss < heatLosses[neighbour]) {

                heatLosses[neighbour] = newHeatLoss;
                unprocessedStates.emplace(neighbour, newHeatLoss);
            }
        }
    }

    return -1;
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
    std::cout << "\tPart 1: " << solution(TEST_INPUT_PART1_PATH, 0, 3) << std::endl;
    std::cout << "\tInput 1 Part 2: " << solution(TEST_INPUT1_PART2_PATH, 4, 10) << std::endl;
    std::cout << "\tInput 2 Part 2: " << solution(TEST_INPUT2_PART2_PATH, 4, 10) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solution(MY_INPUT_PATH, 0, 3) << std::endl;
    std::cout << "\tPart 2: " << solution(MY_INPUT_PATH, 4, 10) << std::endl;
    std::cout << "My input runtime [ms]:" << std::endl;
    std::cout << "\tPart 1: " << measureTime([](){ solution(MY_INPUT_PATH, 0, 3); }, 100) << std::endl;
    std::cout << "\tPart 2: " << measureTime([](){ solution(MY_INPUT_PATH, 4, 10); }, 100) << std::endl;

    return 0;
}
