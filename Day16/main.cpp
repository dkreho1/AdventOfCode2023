#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <set>


#define MY_INPUT_PATH R"(..\inputDay16.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day16.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day16.txt)"


enum class BeamDirection{ right, left, up, down };


void propagateBeam(const std::vector<std::string> &contraption,
                   std::vector<std::vector<std::set<BeamDirection>>> &previousBeamDirections,
                   long long &numOfEnergizedTiles, int currentPosX, int currentPosY,
                   const BeamDirection &beamDirection) {

    if (currentPosX < 0 || currentPosX == contraption.size()) {
        return;
    }

    if (currentPosY < 0 || currentPosY == contraption.at(currentPosX).size()) {
        return;
    }

    if (previousBeamDirections.at(currentPosX).at(currentPosY).contains(beamDirection)) {
        return;
    }

    switch (beamDirection) {
        case BeamDirection::right:
            while (currentPosY < contraption.at(currentPosX).size() &&
                    (contraption.at(currentPosX).at(currentPosY) == '.'
                    || contraption.at(currentPosX).at(currentPosY) == '-')) {
                numOfEnergizedTiles += previousBeamDirections.at(currentPosX).at(currentPosY).empty();
                previousBeamDirections.at(currentPosX).at(currentPosY).insert(beamDirection);
                currentPosY++;
            }

            if (currentPosY == contraption.at(currentPosX).size()) {
                return;
            }

            numOfEnergizedTiles += previousBeamDirections.at(currentPosX).at(currentPosY).empty();
            previousBeamDirections.at(currentPosX).at(currentPosY).insert(beamDirection);

            if (contraption.at(currentPosX).at(currentPosY) == '\\') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX + 1, currentPosY, BeamDirection::down);
                return;
            }

            if (contraption.at(currentPosX).at(currentPosY) == '/') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX - 1, currentPosY, BeamDirection::up);
                return;
            }

            if (contraption.at(currentPosX).at(currentPosY) == '|') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX + 1, currentPosY, BeamDirection::down);
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX - 1, currentPosY, BeamDirection::up);
                return;
            }

        case BeamDirection::left:
            while (currentPosY >= 0 &&
                   (contraption.at(currentPosX).at(currentPosY) == '.'
                    || contraption.at(currentPosX).at(currentPosY) == '-')) {
                numOfEnergizedTiles += previousBeamDirections.at(currentPosX).at(currentPosY).empty();
                previousBeamDirections.at(currentPosX).at(currentPosY).insert(beamDirection);
                currentPosY--;
            }

            if (currentPosY == -1) {
                return;
            }

            numOfEnergizedTiles += previousBeamDirections.at(currentPosX).at(currentPosY).empty();
            previousBeamDirections.at(currentPosX).at(currentPosY).insert(beamDirection);

            if (contraption.at(currentPosX).at(currentPosY) == '\\') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX - 1, currentPosY, BeamDirection::up);
                return;
            }

            if (contraption.at(currentPosX).at(currentPosY) == '/') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX + 1, currentPosY, BeamDirection::down);
                return;
            }

            if (contraption.at(currentPosX).at(currentPosY) == '|') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX + 1, currentPosY, BeamDirection::down);
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX - 1, currentPosY, BeamDirection::up);
                return;
            }

        case BeamDirection::up:
            while (currentPosX >= 0 &&
                   (contraption.at(currentPosX).at(currentPosY) == '.'
                    || contraption.at(currentPosX).at(currentPosY) == '|')) {
                numOfEnergizedTiles += previousBeamDirections.at(currentPosX).at(currentPosY).empty();
                previousBeamDirections.at(currentPosX).at(currentPosY).insert(beamDirection);
                currentPosX--;
            }

            if (currentPosX == -1) {
                return;
            }

            numOfEnergizedTiles += previousBeamDirections.at(currentPosX).at(currentPosY).empty();
            previousBeamDirections.at(currentPosX).at(currentPosY).insert(beamDirection);

            if (contraption.at(currentPosX).at(currentPosY) == '\\') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX, currentPosY - 1, BeamDirection::left);
                return;
            }

            if (contraption.at(currentPosX).at(currentPosY) == '/') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX, currentPosY + 1, BeamDirection::right);
                return;
            }

            if (contraption.at(currentPosX).at(currentPosY) == '-') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX, currentPosY - 1, BeamDirection::left);
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX, currentPosY + 1, BeamDirection::right);
                return;
            }

        case BeamDirection::down:
            while (currentPosX < contraption.size() &&
                   (contraption.at(currentPosX).at(currentPosY) == '.'
                    || contraption.at(currentPosX).at(currentPosY) == '|')) {
                numOfEnergizedTiles += previousBeamDirections.at(currentPosX).at(currentPosY).empty();
                previousBeamDirections.at(currentPosX).at(currentPosY).insert(beamDirection);
                currentPosX++;
            }

            if (currentPosX == contraption.size()) {
                return;
            }

            numOfEnergizedTiles += previousBeamDirections.at(currentPosX).at(currentPosY).empty();
            previousBeamDirections.at(currentPosX).at(currentPosY).insert(beamDirection);

            if (contraption.at(currentPosX).at(currentPosY) == '\\') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX, currentPosY + 1, BeamDirection::right);
                return;
            }

            if (contraption.at(currentPosX).at(currentPosY) == '/') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX, currentPosY - 1, BeamDirection::left);
                return;
            }

            if (contraption.at(currentPosX).at(currentPosY) == '-') {
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX, currentPosY - 1, BeamDirection::left);
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              currentPosX, currentPosY + 1, BeamDirection::right);
                return;
            }
    }
}


long long solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    std::vector<std::string> contraption;
    for (std::string line; std::getline(input, line); contraption.push_back(line));

    std::vector<std::vector<std::set<BeamDirection>>> previousBeamDirections(
            contraption.size(),
            std::vector<std::set<BeamDirection>>(contraption.begin()->size()));
    long long numOfEnergizedTiles{};
    propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                  0, 0, BeamDirection::right);

    return numOfEnergizedTiles;
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    std::vector<std::string> contraption;
    for (std::string line; std::getline(input, line); contraption.push_back(line));

    long long maxNumOfEnergizedTiles{};
    for (int i{}; i < contraption.size(); ++i) {
        for (int j{}; j < contraption.at(i).size(); ++j) {
            if (i != 0 && i + 1 != contraption.size() &&
                j != 0 && j + 1 != contraption.at(i).size()) {
                continue;
            }

            std::set<BeamDirection> possibleInitBeamDirections;

            if (i == 0) {
                possibleInitBeamDirections.insert(BeamDirection::down);
            } else if (i + 1 == contraption.size()) {
                possibleInitBeamDirections.insert(BeamDirection::up);
            }

            if (j == 0) {
                possibleInitBeamDirections.insert(BeamDirection::right);
            } else if (j + 1 == contraption.at(i).size()) {
                possibleInitBeamDirections.insert(BeamDirection::left);
            }

            for (auto&& beamDirection : possibleInitBeamDirections) {
                std::vector<std::vector<std::set<BeamDirection>>> previousBeamDirections(
                        contraption.size(),
                        std::vector<std::set<BeamDirection>>(contraption.begin()->size()));
                long long numOfEnergizedTiles{};
                propagateBeam(contraption, previousBeamDirections, numOfEnergizedTiles,
                              i, j, beamDirection);

                if (numOfEnergizedTiles > maxNumOfEnergizedTiles) {
                    maxNumOfEnergizedTiles = numOfEnergizedTiles;
                }
            }
        }
    }

    return maxNumOfEnergizedTiles;
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
    std::cout << "\tPart 2: " << measureTime([](){ solutionPart2(MY_INPUT_PATH); }, 100) << std::endl;

    return 0;
}
