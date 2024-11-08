#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <chrono>


#define MY_INPUT_PATH R"(..\inputDay5.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day5.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day5.txt)"


long long solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);
    std::string line;
    std::stringstream ss;

    std::getline(input, line);
    line.erase(0, 7);

    std::vector<long long> locations;
    ss.str(line);
    long long seed;
    while(ss >> seed) {
        locations.push_back(seed);
    }
    ss.clear();

    std::string maps[] = {
            "seed-to-soil map:",
            "soil-to-fertilizer map:",
            "fertilizer-to-water map:",
            "water-to-light map:",
            "light-to-temperature map:",
            "temperature-to-humidity map:",
            "humidity-to-location map:"
    };

    std::getline(input, line);
    if (!line.empty()) {
        throw std::runtime_error("No empty line");
    }

    for (auto&& map: maps) {
        std::getline(input, line);
        if (line != map) {
            throw std::runtime_error("Wrong map");
        }

        long long destination, source, length;
        std::vector<bool> changed(locations.size(), false);
        for (; std::getline(input, line) && !line.empty(); ) {
            ss.str(line);
            ss >> destination >> source >> length;
            ss.clear();

            for (int i{}; i < locations.size(); ++i) {
                if (!changed.at(i) && locations.at(i) >= source && locations.at(i) < source + length) {
                    locations.at(i) += destination - source;
                    changed.at(i) = true;
                }
            }
        }
    }

    return *std::min_element(locations.begin(), locations.end());
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);
    std::string line;
    std::stringstream ss;

    std::getline(input, line);
    line.erase(0, 7);

    std::vector<std::pair<long long, long long>> locationRanges;
    ss.str(line);
    long long seedBegin, seedLength;
    while(ss >> seedBegin >> seedLength) {
        locationRanges.emplace_back(seedBegin, seedBegin + seedLength - 1);
    }
    ss.clear();

    std::string maps[] = {
            "seed-to-soil map:",
            "soil-to-fertilizer map:",
            "fertilizer-to-water map:",
            "water-to-light map:",
            "light-to-temperature map:",
            "temperature-to-humidity map:",
            "humidity-to-location map:"
    };

    std::getline(input, line);
    if (!line.empty()) {
        throw std::runtime_error("No empty line");
    }

    for (auto&& map: maps) {
        std::getline(input, line);
        if (line != map) {
            throw std::runtime_error("Wrong map");
        }

        long long destination, source, length;
        std::vector<bool> changed(locationRanges.size(), false);
        for (; std::getline(input, line) && !line.empty(); ) {
            ss.str(line);
            ss >> destination >> source >> length;
            ss.clear();

            for (int i{}; i < locationRanges.size(); ++i) {
                if (changed.at(i)) {
                    continue;
                }

                bool srcBeginInMap{ locationRanges.at(i).first >= source &&
                                    locationRanges.at(i).first < source + length },
                    srcEndInMap{ locationRanges.at(i).second >= source &&
                                 locationRanges.at(i).second < source + length },
                    mapInSrc{ source >= locationRanges.at(i).first &&
                              source + length < locationRanges.at(i).second };

                if (srcBeginInMap && srcEndInMap) {
                    locationRanges.at(i).first += destination - source;
                    locationRanges.at(i).second += destination - source;
                    changed.at(i) = true;
                }

                if (srcBeginInMap && !srcEndInMap) {
                    locationRanges.emplace_back(source + length, locationRanges.at(i).second);
                    changed.push_back(false);

                    locationRanges.at(i).first += destination - source;
                    locationRanges.at(i).second = destination + length - 1;
                    changed.at(i) = true;
                }

                if (!srcBeginInMap && srcEndInMap) {
                    locationRanges.emplace_back(locationRanges.at(i).first, source - 1);
                    changed.push_back(false);

                    locationRanges.at(i).first = destination;
                    locationRanges.at(i).second += destination - source;
                    changed.at(i) = true;
                }

                if (!srcBeginInMap && !srcEndInMap && mapInSrc) {
                    locationRanges.emplace_back(locationRanges.at(i).first, source - 1);
                    changed.push_back(false);

                    locationRanges.emplace_back(source + length, locationRanges.at(i).second);
                    changed.push_back(false);

                    locationRanges.at(i).first = destination;
                    locationRanges.at(i).second = destination + length - 1;
                    changed.at(i) = true;
                }
            }
        }
    }

    return std::min_element(locationRanges.begin(), locationRanges.end(),
                            [](const auto& el1, const auto& el2) -> bool {
                                return el1.first < el2.first;
                            }
                            )->first;
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
