#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


#define MY_INPUT_PATH R"(..\inputDay22.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day22.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day22.txt)"


struct Position3D {
    int x;
    int y;
    int z;
};

struct Brick {
    Position3D corner1;
    Position3D corner2;
    int minZ;
    int maxZ;

    Brick(const Position3D &corner1, const Position3D &corner2) : corner1{ corner1 }, corner2{ corner2 } {
        updateMinMaxZ();
    }

    bool isOverlappingXY(const Brick& brick) const {
        bool overlap_x{ corner2.x >= brick.corner1.x && brick.corner2.x >= corner1.x };
        bool overlap_y{ corner2.y >= brick.corner1.y && brick.corner2.y >= corner1.y };

        return overlap_x && overlap_y;
    }

    void updateMinMaxZ() {
        minZ = std::min(corner1.z, corner2.z);
        maxZ = std::max(corner1.z, corner2.z);
    }
};


int solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    std::vector<Brick> bricks;
    for (std::string line; std::getline(input, line); ) {
        std::stringstream ss(line);

        int x, y, z;
        char commaOrTilda;

        ss >> x >> commaOrTilda >> y >> commaOrTilda >> z >> commaOrTilda;
        Position3D corner1{x, y, z};

        ss >> x >> commaOrTilda >> y >> commaOrTilda >> z;
        Position3D corner2{x, y, z};

        bricks.emplace_back(corner1, corner2);
    }

    std::sort(
        bricks.begin(),
        bricks.end(),
        [](const Brick& brick1, const Brick& brick2) {
            return std::min(brick1.corner1.z, brick1.corner2.z) <
                   std::min(brick2.corner1.z, brick2.corner2.z);
        }
    );

    for (int i{}; i < bricks.size(); ++i) {
        if (i == 0) {
            if (bricks.at(i).minZ != 1) {
                bricks.at(i).corner1.z += -bricks.at(i).minZ + 1;
                bricks.at(i).corner2.z += -bricks.at(i).minZ + 1;
                bricks.at(i).updateMinMaxZ();
            }

            continue;
        }

        int maxZ{};
        for (int j{}; j < i; ++j) {
            if (
                bricks.at(i).isOverlappingXY(bricks.at(j)) &&
                bricks.at(j).maxZ > maxZ
            ) {
                maxZ = bricks.at(j).maxZ;
            }
        }

        bricks.at(i).corner1.z += -bricks.at(i).minZ + 1 + maxZ;
        bricks.at(i).corner2.z += -bricks.at(i).minZ + 1 + maxZ;
        bricks.at(i).updateMinMaxZ();
    }

    int numOfSafeToDisintegrated{};

    for (auto brickIt{ bricks.begin() }; brickIt != bricks.end(); ++brickIt) {
        bool safeToDisintegrated{ true };
        for (auto otherBrickIt{ brickIt + 1 }; otherBrickIt != bricks.end(); ++otherBrickIt) {
            if (
                otherBrickIt->minZ == brickIt->maxZ + 1 &&
                brickIt->isOverlappingXY(*otherBrickIt)
            ) {
                bool supportBrickFound{ false };
                for (auto supportBrick{ bricks.begin() }; supportBrick != bricks.end(); ++supportBrick) {
                    if (
                        brickIt != supportBrick &&
                        brickIt->maxZ == supportBrick->maxZ &&
                        supportBrick->isOverlappingXY(*otherBrickIt)
                    ) {
                        supportBrickFound = true;
                        break;
                    }
                }

                if (!supportBrickFound) {
                    safeToDisintegrated = false;
                    break;
                }
            }
        }

        numOfSafeToDisintegrated += safeToDisintegrated;
    }

    return numOfSafeToDisintegrated;
}


int solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    return 0;
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
//    std::cout << "\tPart 2: " << solutionPart2(TEST_INPUT_PART2_PATH) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(MY_INPUT_PATH) << std::endl;
//    std::cout << "\tPart 2: " << solutionPart2(MY_INPUT_PATH) << std::endl;
    std::cout << "My input runtime [ms]:" << std::endl;
    std::cout << "\tPart 1: " << measureTime([](){ solutionPart1(MY_INPUT_PATH); }, 1000) << std::endl;
//    std::cout << "\tPart 2: " << measureTime([](){ solutionPart2(MY_INPUT_PATH); }, 1000) << std::endl;

    return 0;
}
