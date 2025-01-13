#include "Transducer.h"
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;

string Transducer::compare(const int a, const int b) {
    return (a < b) ? "<" : (a == b ? "=" : ">");
}

vector<Semantic::Letter> Transducer::process(const vector<int>& series, const nlohmann::json& patternJson) {
    vector<Semantic::Letter> result;
    size_t seriesSize = series.size();
    if (seriesSize < 2) return result;

    result.reserve(seriesSize - 1);

    // Cache frequently used JSON components
    const auto& states = patternJson.at("states");
    string state = patternJson.at("entry").get<string>();

    for (size_t i = 1; i < seriesSize; ++i) {
        string comparison = compare(series[i - 1], series[i]);
        const auto& stateConditions = states.at(state);

        for (const auto& condition : stateConditions) {
            if (condition.at("condition").get<string>() == comparison) {
                state = condition.at("next").get<string>();
                result.emplace_back(Semantic::string_to_letter(condition.at("semantic").get<string>()));
                break;
            }
        }
    }

    return result;
}