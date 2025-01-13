#include "Transducer.h"
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

using namespace std;

struct PairHash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1);
    }
};

// Pre-computed comparison results
inline char Transducer::compare(const int a, const int b) {
    return (a < b) ? '<' : (a == b ? '=' : '>');
}

vector<Semantic::Letter> Transducer::process(const vector<int>& series, const nlohmann::json& patternJson) {
    const size_t seriesSize = series.size();
    if (seriesSize < 2) return {};

    vector<Semantic::Letter> result;
    result.reserve(seriesSize - 1);

    // Pre-process state transitions into a more efficient structure
    using TransitionKey = pair<string, char>;
    struct TransitionValue {
        string nextState;
        Semantic::Letter semantic;
    };

    unordered_map<TransitionKey, TransitionValue, PairHash> transitionMap;
    const auto& states = patternJson.at("states");

    // Build transition map
    for (const auto& [stateName, stateConditions] : states.items()) {
        for (const auto& condition : stateConditions) {
            TransitionKey key = {
                stateName,
                condition.at("condition").get<string>()[0]  // Get first char of condition string
            };
            TransitionValue value = {
                condition.at("next").get<string>(),
                Semantic::string_to_letter(condition.at("semantic").get<string>())
            };
            transitionMap[key] = value;
        }
    }

    // Process series using optimized transition map
    string currentState = patternJson.at("entry").get<string>();

    // Pre-compute all comparisons
    vector<char> comparisons;
    comparisons.reserve(seriesSize - 1);
    for (size_t i = 1; i < seriesSize; ++i) {
        comparisons.push_back(compare(series[i - 1], series[i]));
    }

    // Process transitions
    for (size_t i = 0; i < comparisons.size(); ++i) {
        const auto& transition = transitionMap[{currentState, comparisons[i]}];
        currentState = transition.nextState;
        result.push_back(transition.semantic);
    }

    return result;
}