#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>


#define MY_INPUT_PATH R"(..\inputDay2.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day2.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day2.txt)"


int solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    std::map<std::string, int> colorCubeLimits {
            {"red", 12}, {"green", 13}, {"blue", 14}
    };

    int sumIDs{};

    for (std::string line; std::getline(input, line); ) {
        bool possible{true};

        for (auto&& cube: colorCubeLimits) {
            std::string mutableLine = line;

            std::regex exp(std::string(R"(\d+ )").append(cube.first));
            std::smatch sm;

            while (std::regex_search(mutableLine, sm, exp)) {
                int numberOfCubes;
                std::stringstream ss(sm.str());
                ss >> numberOfCubes;

                if (cube.second < numberOfCubes) {
                    possible = false;
                    break;
                }

                mutableLine = sm.suffix().str();
            }

            if (!possible) {
                break;
            }
        }

        if (possible) {
            std::stringstream ss(line);
            std::string gameStr;
            int num;
            ss >> gameStr >> num;
            sumIDs += num;
        }
    }

    return sumIDs;
}


int solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    int sumOfPowers{};

    for (std::string line; std::getline(input, line); ) {
        std::map<std::string, int> maxNumOfCubes {
                {"red", 0}, {"green", 0}, {"blue", 0}
        };

        for (auto&& cube: maxNumOfCubes) {
            std::string mutableLine = line;

            std::regex exp(std::string(R"(\d+ )").append(cube.first));
            std::smatch sm;

            while (std::regex_search(mutableLine, sm, exp)) {
                std::stringstream ss(sm.str());
                int num;
                ss >> num;
                if (cube.second < num) {
                    cube.second = num;
                }

                mutableLine = sm.suffix().str();
            }
        }

        sumOfPowers += maxNumOfCubes["red"] * maxNumOfCubes["green"] * maxNumOfCubes["blue"];
    }

    return sumOfPowers;
}


int main() {
    std::cout << "Test inputs:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(TEST_INPUT_PART1_PATH) << std::endl;
    std::cout << "\tPart 2: " << solutionPart2(TEST_INPUT_PART2_PATH) << std::endl;
    std::cout << "My input:" << std::endl;
    std::cout << "\tPart 1: " << solutionPart1(MY_INPUT_PATH) << std::endl;
    std::cout << "\tPart 2: " << solutionPart2(MY_INPUT_PATH) << std::endl;

    return 0;
}
