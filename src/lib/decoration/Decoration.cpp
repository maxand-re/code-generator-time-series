#include "Decoration.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../transducers/Transducer.h"

map<string, function<bool(int, int)> > operators = {
    {"min", [](int x, int y) { return x < y; }},
    {"max", [](int x, int y) { return x > y; }}
};

map<string, function<int(int, int)> > aggregators = {
    {"min", [](int x, int y) { return min(x, y); }},
    {"max", [](int x, int y) { return max(x, y); }},
    {"sum", [](int x, int y) { return x + y; }},
};



nlohmann::json Decoration::get_json(const string &pattern) {
    nlohmann::json patternJson;

    ifstream file("resources/transducers/" + pattern + ".json");
    if (!file.is_open()) {
        throw runtime_error("The selected pattern does not exist.");
    }

    file >> patternJson;

    file.close();

    return patternJson;
}

int calculate_operator(const string &operator_string, int valueA, int valueB) {
    if (operator_string == "+") {
        return valueA + valueB;
    }

    if (operator_string == "max") {
        return max(valueA, valueB);
    }

    if (operator_string == "min") {
        return min(valueA, valueB);
    }

    return 0;
}

Decoration::Result Decoration::apply_decorator(
    const vector<int> &series,
    int default_gf,
    int neutral_f,
    int delta_f,
    const string &operator_string,
    const string &aggregator_string,
    const string &pattern
) {
    int C = default_gf;
    int D = neutral_f;
    int R = default_gf;

    const auto json = get_json(pattern);

    auto semantics = Transducer::process(series, json);

    const int after = json.at("after").get<int>();

    vector<int *> at(series.size(), new int(0));
    vector<int *> ct(series.size(), new int(0));
    vector<int *> f(series.size(), new int(0));

    for (auto i = 0; i < semantics.size(); ++i) {
        const int current_delta_f = delta_f == -1 ? series[i] : delta_f;
        const int current_delta_f_1 = delta_f == -1 ? series[i + 1] : delta_f;

        switch (semantics[i]) {
            case Semantic::OUT: //
                f[i] = new int(0);
                ct[i] = ct[i + 1];
                at[i] = at[i + 1];

                break;
            case Semantic::OUT_R: //
                f[i] = new int(0);
                ct[i] = ct[i + 1];
                at[i] = at[i + 1];

                D = neutral_f;
                break;
            case Semantic::OUT_A:
                break;
            case Semantic::MAYBE_B: //
                f[i] = new int(0);
                ct[i] = ct[i + 1];
                at[i] = at[i + 1];

                D = calculate_operator(operator_string, D, current_delta_f);
                break;
            case Semantic::MAYBE_A:
                break;
            case Semantic::FOUND:
                break;
            case Semantic::FOUND_E: //
                if (after == 0) {
                    if (operators.at(aggregator_string)(calculate_operator(operator_string,
                                                                           calculate_operator(
                                                                               operator_string, D, current_delta_f),
                                                                           current_delta_f_1), R)) {
                        f[i] = ct[i];
                        at[i] = new int(0);
                        ct[i] = at[i + 1];
                    } else if (calculate_operator(operator_string,
                                                  calculate_operator(operator_string, D, current_delta_f),
                                                  current_delta_f_1) == R) {
                        f[i] = at[i + 1];
                        ct[i] = at[i + 1];
                        at[i] = at[i + 1];
                    } else if (operators.at(aggregator_string)(R, calculate_operator(operator_string,
                                                                   calculate_operator(
                                                                       operator_string, D, current_delta_f),
                                                                   current_delta_f_1))) {
                        f[i] = new int(0);
                        ct[i] = new int(0);
                        at[i] = at[i + 1];
                    } else {
                        continue;
                    }

                    R = aggregators.at(aggregator_string)(R,
                                                          calculate_operator(operator_string,
                                                                             calculate_operator(operator_string,
                                                                                 D, current_delta_f),
                                                                             current_delta_f_1)
                    );

                    D = neutral_f;
                } else if (after == 1) {
                    if (operators.at(aggregator_string)(calculate_operator(operator_string, D, current_delta_f), R)) {
                        f[i] = ct[i];
                        at[i] = new int(0);
                        ct[i] = at[i + 1];
                    } else if (calculate_operator(operator_string, D, current_delta_f) == R) {
                        f[i] = at[i + 1];
                        ct[i] = at[i + 1];
                        at[i] = at[i + 1];
                    } else if (operators.at(aggregator_string)(
                        R, calculate_operator(operator_string, D, current_delta_f))) {
                        f[i] = new int(0);
                        ct[i] = new int(0);
                        at[i] = at[i + 1];
                    } else {
                        continue;
                    }

                    R = aggregators.at(aggregator_string)(R, calculate_operator(operator_string, D, current_delta_f));

                    D = neutral_f;
                }

                break;
            case Semantic::IN:
                break;
            default: throw std::invalid_argument("Invalid Semantic::Letter value");
        }
    }

    const unsigned long n = semantics.size() - 1;

    if (operators.at(aggregator_string)(C, R)) {
        ct[n] = new int(1);
        at[n] = new int(1);
    } else if (C == R) {
        if (R == default_gf) {
            ct[n] = new int(0);
            at[n] = new int(0);
        } else {
            ct[n] = new int(1);
            at[n] = new int(1);
        }
    } else {
        ct[n] = new int(0);
        at[n] = new int(1);
    }

    return {
        .at=at,
        .ct=ct,
        .f=f,
        .R=R,
        .C=C,
        .D=D
    };
}
