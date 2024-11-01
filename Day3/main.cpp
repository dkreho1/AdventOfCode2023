#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>


#define MY_INPUT_PATH R"(..\inputDay3.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day3.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day3.txt)"


struct PartNumber {
    int value;
    int row;
    int columnStart;
    int columnEnd;

    bool isAdjacent(int row, int column) const {
        return (row == this->row && (column - 1 == this->columnEnd || column + 1 == this->columnStart)) ||
               ((row - 1 == this->row || row + 1 == this->row)
                    && column >= this->columnStart - 1 && column <= this->columnEnd + 1);
    }
};


int solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);
    std::vector<std::string> engineSchematic;
    std::vector<PartNumber> partNumbers;

    for (std::string line; std::getline(input, line); ) {
        std::string mutableLine = line;

        std::regex exp(R"(\d+)");
        std::smatch sm;

        int prevPosition = 0;
        while (std::regex_search(mutableLine, sm, exp)) {
            partNumbers.push_back({
                std::stoi(sm.str()),
                static_cast<int>(engineSchematic.size()),
                prevPosition + sm.position(),
                prevPosition + sm.position() + sm.length() - 1
            });

            prevPosition += sm.position() + sm.length();
            mutableLine = sm.suffix().str();
        }

        engineSchematic.push_back(line);
    }

    int partsSum{};

    for (int symbolRow = 0; symbolRow < engineSchematic.size(); ++symbolRow) {
        std::string mutableLine = engineSchematic.at(symbolRow);

        std::regex exp(R"([^\d\.])");
        std::smatch sm;

        int prevPosition = 0;
        while (std::regex_search(mutableLine, sm, exp)) {
            int symbolColumn{ prevPosition + sm.position() };

            std::vector<PartNumber>::iterator it;
            while (
                (it = std::find_if(partNumbers.begin(), partNumbers.end(),
                    [symbolRow, symbolColumn] (const PartNumber &number) -> bool {
                        return number.isAdjacent(symbolRow, symbolColumn);
                    }
                )) != partNumbers.end()
            ) {
                partsSum += it->value;
                partNumbers.erase(it);
            }

            prevPosition += sm.position() + sm.length();
            mutableLine = sm.suffix().str();
        }
    }

    return partsSum;
}


int solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);
    std::vector<std::string> engineSchematic;
    std::vector<PartNumber> partNumbers;

    for (std::string line; std::getline(input, line); ) {
        std::string mutableLine = line;

        std::regex exp(R"(\d+)");
        std::smatch sm;

        int prevPosition = 0;
        while (std::regex_search(mutableLine, sm, exp)) {
            partNumbers.push_back({
                std::stoi(sm.str()),
                static_cast<int>(engineSchematic.size()),
                prevPosition + sm.position(),
                prevPosition + sm.position() + sm.length() - 1
            });

            prevPosition += sm.position() + sm.length();
            mutableLine = sm.suffix().str();
        }

        engineSchematic.push_back(line);
    }

    int gearRatioSum{};

    for (int symbolRow = 0; symbolRow < engineSchematic.size(); ++symbolRow) {
        std::string mutableLine = engineSchematic.at(symbolRow);

        std::regex exp(R"(\*)");
        std::smatch sm;

        int prevPosition = 0;
        while (std::regex_search(mutableLine, sm, exp)) {
            int symbolColumn{ prevPosition + sm.position() }, ratio{ 1 };

            if (
                std::count_if(partNumbers.begin(), partNumbers.end(),
                    [symbolRow, symbolColumn, &ratio] (const PartNumber &number) -> bool {
                        if (number.isAdjacent(symbolRow, symbolColumn)) {
                            ratio *= number.value;
                            return true;
                        }

                        return false;
                    }
                ) == 2
            ) {
                gearRatioSum += ratio;
            }

            prevPosition += sm.position() + sm.length();
            mutableLine = sm.suffix().str();
        }
    }

    return gearRatioSum;
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
