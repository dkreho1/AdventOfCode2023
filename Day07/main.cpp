#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>
#include <chrono>
#include <functional>


#define MY_INPUT_PATH R"(..\inputDay7.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day7.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day7.txt)"


enum class CardType{ HighCard, OnePair, TwoPair, ThreeOfAKind, FullHouse, FourOfAKind, FiveOfAKind };
using Hand = std::tuple<std::string, int, CardType>;
const int numOfCards{ 5 };


long long solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    const std::string possibleCardValues{ "AKQJT98765432" };

    std::vector<Hand> hands;
    std::string cards;
    int bid;

    while (input >> cards >> bid) {
        CardType type;
        std::map<char, int> count;

        for (auto&& c : cards) {
            count[c]++;
        }

        bool assigned{ false };
        switch (count.size()) {
            case 1:
                type = CardType::FiveOfAKind;
                break;

            case 2:
                for(auto&& c : count) {
                    if (c.second == 4) {
                        type = CardType::FourOfAKind;
                        assigned = true;
                        break;
                    }
                }

                if (!assigned) {
                    type = CardType::FullHouse;
                }

                break;

            case 3:
                for(auto&& c : count) {
                    if (c.second == 3) {
                        type = CardType::ThreeOfAKind;
                        assigned = true;
                        break;
                    }
                }

                if (!assigned) {
                    type = CardType::TwoPair;
                }

                break;

            case 4:
                type = CardType::OnePair;
                break;

            case 5:
                type = CardType::HighCard;
                break;
        }

        hands.emplace_back(cards, bid, type);
    }

    std::sort(hands.begin(), hands.end(),
              [possibleCardValues](const Hand& hand1, const Hand& hand2) -> bool {
        if (std::get<2>(hand1) == std::get<2>(hand2)) {
            for (int i{}; i < numOfCards; ++i) {
                if (std::get<0>(hand1).at(i) != std::get<0>(hand2).at(i)) {
                    return possibleCardValues.find(std::get<0>(hand1).at(i)) >
                        possibleCardValues.find(std::get<0>(hand2).at(i));
                }
            }
        }

        return std::get<2>(hand1) < std::get<2>(hand2);
    });

    int rank{ 1 };
    long long totalWinnings{};
    for (auto&& hand : hands) {
        totalWinnings += std::get<1>(hand) * rank;
        rank++;
    }

    return totalWinnings;
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    const std::string possibleCardValues{ "AKQT98765432J" };

    std::vector<Hand> hands;
    std::string cards;
    int bid;

    while (input >> cards >> bid) {
        CardType type;
        std::map<char, int> count;

        for (auto&& c : cards) {
            count[c]++;
        }

        if (count['J'] != 0 && count['J'] != 5) {
            char maxCard = 0;

            for (auto&& c : count) {
                if (c.first == 'J') {
                    continue;
                }

                if (maxCard == 0) {
                    maxCard = c.first;
                    continue;
                }

                if (count[maxCard] < c.second) {
                    maxCard = c.first;
                }
            }

            count[maxCard] += count['J'];
        }

        if (count['J'] != 5) {
            count.erase('J');
        }

        bool assigned{ false };
        switch (count.size()) {
            case 1:
                type = CardType::FiveOfAKind;
                break;

            case 2:
                for(auto&& c : count) {
                    if (c.second == 4) {
                        type = CardType::FourOfAKind;
                        assigned = true;
                        break;
                    }
                }

                if (!assigned) {
                    type = CardType::FullHouse;
                }

                break;

            case 3:
                for(auto&& c : count) {
                    if (c.second == 3) {
                        type = CardType::ThreeOfAKind;
                        assigned = true;
                        break;
                    }
                }

                if (!assigned) {
                    type = CardType::TwoPair;
                }

                break;

            case 4:
                type = CardType::OnePair;
                break;

            case 5:
                type = CardType::HighCard;
                break;
        }

        hands.emplace_back(cards, bid, type);
    }

    std::sort(hands.begin(), hands.end(),
              [possibleCardValues](const Hand& hand1, const Hand& hand2) -> bool {
                  if (std::get<2>(hand1) == std::get<2>(hand2)) {
                      for (int i{}; i < numOfCards; ++i) {
                          if (std::get<0>(hand1).at(i) != std::get<0>(hand2).at(i)) {
                              return possibleCardValues.find(std::get<0>(hand1).at(i)) >
                                     possibleCardValues.find(std::get<0>(hand2).at(i));
                          }
                      }
                  }

                  return std::get<2>(hand1) < std::get<2>(hand2);
              });

    int rank{ 1 };
    long long totalWinnings{};
    for (auto&& hand : hands) {
        totalWinnings += std::get<1>(hand) * rank;
        rank++;
    }

    return totalWinnings;
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
