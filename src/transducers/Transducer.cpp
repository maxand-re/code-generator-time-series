#include "Transducer.h"

#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using namespace std;

string Transducer::compare(const int a, const int b) {
    if (a < b) return "<";
    if (a == b) return "=";
    return ">";
}

vector<Semantic::Letter> Transducer::process(vector<int> series, string pattern) {
    ifstream file("resources/transducers/" + pattern + ".json");
    if (!file.is_open()) {
        throw runtime_error("The selected pattern does not exist.");
    }

    nlohmann::json patternJson;
    file >> patternJson;

    vector<Semantic::Letter> result;
    auto state = patternJson.at("entry").get<string>();

    for (unsigned int i = 1; i < series.size(); ++i) {
        auto comparison = compare(series[i - 1], series[i]);
        auto conditionIter = patternJson.at("states").at(state).begin();
        auto conditionEnd = patternJson.at("states").at(state).end();

        for (; conditionIter != conditionEnd; ++conditionIter) {
            if (conditionIter.value().at("condition").get<string>() == comparison) {

                state = conditionIter.value().at("next").get<string>();
                auto stringSemanticLetter = conditionIter.value().at("semantic").get<string>();
                result.push_back(Semantic::string_to_letter(stringSemanticLetter));
                break;
            }
        }
    }

    file.close();

    return result;
}
