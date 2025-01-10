#include "Transducer.h"

#include <fstream>

using namespace std;

string Transducer::compare(const int a, const int b) {
    if (a < b) return "<";
    if (a == b) return "=";
    return ">";
}

vector<Semantic::Letter> Transducer::process(const vector<int> &series, nlohmann::json patternJson) {
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

    return result;
}
