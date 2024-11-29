#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <regex>
#include <string>
#include <optional>
#include <map>
#include <numeric>
#include <cstdio>
#include <array>

#define MY_INPUT_PATH R"(..\inputDay19.txt)"
#define TEST_INPUT_PART1_PATH R"(..\testInputPart1Day19.txt)"
#define TEST_INPUT_PART2_PATH R"(..\testInputPart2Day19.txt)"


enum class Relation { lessThan, greaterThan, jump };

struct Rule {
    Relation relation;
    int boundaryValue;
    std::string destinationWorkflow;
    char ruleType;

    std::optional<std::string> operator() (int value) const {
        if ((relation == Relation::lessThan && value < boundaryValue) ||
            (relation == Relation::greaterThan && value > boundaryValue) ||
             relation == Relation::jump) {
            return destinationWorkflow;
        }

        return std::nullopt;
    }
};


long long solutionPart1(const char* inputPath) {
    std::ifstream input(inputPath);

    std::map<std::string, std::vector<Rule>> workflows;
    for (std::string line; std::getline(input, line) && !line.empty(); ) {
        std::string workflowName{ line.substr(0, line.find('{')) };

        std::regex expWorkflow(R"([^,{}]+(?=,|}))");
        std::smatch smWorkflow;

        std::string mutableLine{ line };
        while (std::regex_search(mutableLine, smWorkflow, expWorkflow)) {
            std::string ruleStr{ smWorkflow.str() };

            Rule rule;
            if (ruleStr.find('<') != std::string::npos) {
                rule.relation = Relation::lessThan;
            } else if (ruleStr.find('>') != std::string::npos) {
                rule.relation = Relation::greaterThan;
            } else {
                rule.relation = Relation::jump;
                rule.destinationWorkflow = ruleStr;
                workflows[workflowName].push_back(rule);
                mutableLine = smWorkflow.suffix().str();
                continue;
            }

            std::regex expRule(R"([^<>:]+)");
            std::smatch smRule;

            std::regex_search(ruleStr, smRule, expRule);
            rule.ruleType = smRule.str().at(0);
            ruleStr = smRule.suffix().str();

            std::regex_search(ruleStr, smRule, expRule);
            rule.boundaryValue = std::stoi(smRule.str());
            ruleStr = smRule.suffix().str();

            std::regex_search(ruleStr, smRule, expRule);
            rule.destinationWorkflow = smRule.str();

            workflows[workflowName].push_back(rule);

            mutableLine = smWorkflow.suffix().str();
        }
    }

    long long sumOfAcceptedParts{};

    for (std::string line; std::getline(input, line); ) {
        std::vector<int> part(4);
        std::sscanf(line.c_str(), "{x=%d,m=%d,a=%d,s=%d}",
                     &part.at(0), &part.at(1), &part.at(2), &part.at(3));

        std::string currentWorkflow{ "in" }, partCategories{ "xmas" };
        while (currentWorkflow != "A" && currentWorkflow != "R") {
            for (auto&& rule : workflows.at(currentWorkflow)) {
                bool ruleApplied{ false };

                for (int i{}; i < 4; ++i) {
                    if ((ruleApplied = rule.ruleType == partCategories.at(i) && rule(part.at(i)))) {
                        currentWorkflow = *rule(part.at(i));
                        break;
                    }
                }

                if (ruleApplied) {
                    break;
                }
            }
        }

        if (currentWorkflow == "A") {
            sumOfAcceptedParts += std::accumulate(part.begin(), part.end(), 0);
        }
    }

    return sumOfAcceptedParts;
}


struct Tesseract {
    std::array<int, 4> lowerCorner{ 1, 1, 1, 1 };
    std::array<int, 4> upperCorner{ 4000, 4000, 4000, 4000 };

    long long volume() {
        long long vol{ 1 };

        for (int i{}; i < 4; ++i) {
            vol *= upperCorner.at(i) - lowerCorner.at(i) + 1;
        }

        return vol;
    }
};


long long findAllPossibleAcceptedParts(
        const std::map<std::string, std::vector<Rule>>& workflows,
        const std::string& currentWorkflow,
        Tesseract currentParts = Tesseract()
        ) {

    if (currentWorkflow == "A") {
        return currentParts.volume();
    }

    if (currentWorkflow == "R") {
        return 0;
    }

    long long totalNumberOfAcceptedParts{};
    std::string partCategories{ "xmas" };
    for (auto&& rule : workflows.at(currentWorkflow)) {
        auto partCategory{ partCategories.find(rule.ruleType) };
        Tesseract newCurrentPart{ currentParts };

        switch (rule.relation) {
            case Relation::lessThan:
                newCurrentPart.upperCorner.at(partCategory) = rule.boundaryValue - 1;
                currentParts.lowerCorner.at(partCategory) = rule.boundaryValue;
                totalNumberOfAcceptedParts +=
                        findAllPossibleAcceptedParts(workflows, rule.destinationWorkflow, newCurrentPart);
                break;

            case Relation::greaterThan:
                newCurrentPart.lowerCorner.at(partCategory) = rule.boundaryValue + 1;
                currentParts.upperCorner.at(partCategory) = rule.boundaryValue;
                totalNumberOfAcceptedParts +=
                        findAllPossibleAcceptedParts(workflows, rule.destinationWorkflow, newCurrentPart);
                break;

            case Relation::jump:
                totalNumberOfAcceptedParts +=
                        findAllPossibleAcceptedParts(workflows, rule.destinationWorkflow, currentParts);
                break;
        }
    }

    return totalNumberOfAcceptedParts;
}


long long solutionPart2(const char* inputPath) {
    std::ifstream input(inputPath);

    std::map<std::string, std::vector<Rule>> workflows;
    for (std::string line; std::getline(input, line) && !line.empty(); ) {
        std::string workflowName{ line.substr(0, line.find('{')) };

        std::regex expWorkflow(R"([^,{}]+(?=,|}))");
        std::smatch smWorkflow;

        std::string mutableLine{ line };
        while (std::regex_search(mutableLine, smWorkflow, expWorkflow)) {
            std::string ruleStr{ smWorkflow.str() };

            Rule rule;
            if (ruleStr.find('<') != std::string::npos) {
                rule.relation = Relation::lessThan;
            } else if (ruleStr.find('>') != std::string::npos) {
                rule.relation = Relation::greaterThan;
            } else {
                rule.relation = Relation::jump;
                rule.destinationWorkflow = ruleStr;
                workflows[workflowName].push_back(rule);
                mutableLine = smWorkflow.suffix().str();
                continue;
            }

            std::regex expRule(R"([^<>:]+)");
            std::smatch smRule;

            std::regex_search(ruleStr, smRule, expRule);
            rule.ruleType = smRule.str().at(0);
            ruleStr = smRule.suffix().str();

            std::regex_search(ruleStr, smRule, expRule);
            rule.boundaryValue = std::stoi(smRule.str());
            ruleStr = smRule.suffix().str();

            std::regex_search(ruleStr, smRule, expRule);
            rule.destinationWorkflow = smRule.str();

            workflows[workflowName].push_back(rule);

            mutableLine = smWorkflow.suffix().str();
        }
    }

    return findAllPossibleAcceptedParts(workflows, "in");
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
    std::cout << "\tPart 1: " << measureTime([](){ solutionPart1(MY_INPUT_PATH); }, 100) << std::endl;
    std::cout << "\tPart 2: " << measureTime([](){ solutionPart2(MY_INPUT_PATH); }, 100) << std::endl;

    return 0;
}
