#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>


#define MY_INPUT_PATH R"(..\inputDay23.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day23.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day23.txt)"


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

    Position operator+(const Position& position) const {
        return { x + position.x, y + position.y };
    }

    bool operator==(const Position& position) const {
        return x == position.x && y == position.y;
    }
};

template <>
struct std::hash<Position> {
    std::size_t operator()(const Position& position) const {
        return std::hash<int>()(position.x) ^ (std::hash<int>()(position.y) << 1);
    }
};


void findLongestHike(
    const std::vector<std::string>& map,
    std::unordered_set<Position> visited,
    Position currentPosition,
    const Position& endPosition,
    int& longestHike,
    bool slipperySlopes
) {
    const std::unordered_map<Position, char> slopes {
        { Position{ -1,  0 }, '^' },
        { Position{  1,  0 }, 'v' },
        { Position{  0, -1 }, '<' },
        { Position{  0,  1 }, '>' }
    };

    while (true) {
        if (visited.contains(currentPosition)) {
            break;
        }

        visited.insert(currentPosition);

        if (endPosition == currentPosition) {
            if (int hikeLength{ int(visited.size() - 1) }; hikeLength > longestHike) {
                longestHike = hikeLength;
            }
            break;
        }

        std::vector<Position> newPositions;
        for (
            const Position& increment : {
                Position{ -1, 0 }, Position{ 1, 0 }, Position{ 0, -1 }, Position{ 0, 1 }
            }
        ) {
            Position newPosition{ currentPosition + increment };

            if (
                !newPosition.isValid() ||
                map.at(newPosition.x).at(newPosition.y) == '#' ||
                (slipperySlopes && map.at(newPosition.x).at(newPosition.y) != '.' &&
                    slopes.at(increment) != map.at(newPosition.x).at(newPosition.y))
                ) {
                continue;
            }

            newPositions.push_back(newPosition);
        }

        if (newPositions.empty()) {
            break;
        }

        if (newPositions.size() == 1) {
            currentPosition = newPositions.front();
            continue;
        }

        for (auto&& newPosition : newPositions) {
            findLongestHike(map, visited, newPosition, endPosition, longestHike, slipperySlopes);
        }
    }
}


int solution(const char* inputPath, bool slipperySlopes) {
    std::ifstream input(inputPath);

    std::vector<std::string> map;
    for (std::string line; std::getline(input, line); map.push_back(line));

    Position::maxX = map.size() - 1;
    Position::maxY = map.front().length() - 1;

    Position startPosition, endPosition;
    startPosition.x = 0;
    startPosition.y = map.at(startPosition.x).find('.');
    endPosition.x = map.size() - 1;
    endPosition.y = map.at(endPosition.x).find('.');

    std::unordered_set<Position> visited;
    int longestHike{};
    findLongestHike(map, visited, startPosition, endPosition, longestHike, slipperySlopes);

    return longestHike;
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
    std::cout << "\tPart 1: " << solution(TEST_INPUT_PART1_PATH, true) << std::endl;
    std::cout << "\tPart 2: " << solution(TEST_INPUT_PART1_PATH, false) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solution(MY_INPUT_PATH, true) << std::endl;
//    std::cout << "\tPart 2: " << solution(MY_INPUT_PATH, false) << std::endl;
    std::cout << "My input runtime [ms]:" << std::endl;
    std::cout << "\tPart 1: " << measureTime([](){ solution(MY_INPUT_PATH, true); }, 10) << std::endl;
//    std::cout << "\tPart 2: " << measureTime([](){ solutionPart2(MY_INPUT_PATH); }, 1000) << std::endl;

    return 0;
}
