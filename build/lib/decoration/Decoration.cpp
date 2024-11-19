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
    if (default_gf == -1)
        default_gf = static_cast<int>(series.size());
    int C = default_gf;
    int D = neutral_f;
    int R = default_gf;

    const auto json = get_json(pattern);

    auto semantics = Transducer::process(series, json);

    const int after = json.at("after").get<int>();

    vector<Node> at(series.size());
    vector<Node> ct(series.size());
    vector<Node> f(series.size());

    for (int i = 0; i < series.size(); i++) {
        at[i] = Node(0);
        ct[i] = Node(0);
        f[i] = Node(0);
    }

    cout << "semantics: ";
    for (auto i = 0; i < semantics.size(); ++i) {
        cout << letter_to_string(semantics[i]) << ",";
    }
    cout << endl;


    for (auto i = 0; i < semantics.size(); ++i) {
        const int current_delta_f = delta_f == -1 ? series[i] : delta_f;
        const int current_delta_f_1 = delta_f == -1 ? series[i + 1] : delta_f;

        switch (semantics[i]) {
            case Semantic::OUT: //
                f[i].setValue(0);
                ct[i].ptr = &ct[i + 1];
                at[i].ptr = &at[i + 1];

                break;
            case Semantic::OUT_R: //
                f[i].setValue(0);
                ct[i].ptr = &ct[i + 1];
                at[i].ptr = &at[i + 1];

                D = neutral_f;
                break;
            case Semantic::OUT_A:
                if (operators.at(aggregator_string)(C, R)) {
                    f[i].setValue(0);
                    at[i].setValue(0);
                    ct[i].ptr = &at[i + 1];
                } else if (C == R) {
                    f[i].setValue(0);
                    ct[i].ptr = &at[i + 1];
                    at[i].ptr = &at[i + 1];
                } else if (operators.at(aggregator_string)(R, C)) {
                    f[i].setValue(0);
                    ct[i].setValue(0);
                    at[i].ptr = &at[i + 1];
                } else {
                }

                C = default_gf;
                D = neutral_f;
                R = aggregators.at(aggregator_string)(R, C);
                break;
            case Semantic::MAYBE_B: //
                f[i].setValue(0);
                ct[i].ptr = &ct[i + 1];
                at[i].ptr = &at[i + 1];

                D = calculate_operator(operator_string, D, current_delta_f);
                break;
            case Semantic::MAYBE_A:
                f[i].setValue(0);
                ct[i].ptr = &ct[i + 1];
                at[i].ptr = &at[i + 1];
                if (after == 0) {
                    D = calculate_operator(operator_string, D, current_delta_f_1);
                } else {
                    D = calculate_operator(operator_string, D, current_delta_f);
                }
                break;
            case Semantic::FOUND:
                ct[i].setValue(0);
                f[i].ptr = &ct[i + 1];
                at[i].ptr = &at[i + 1];

                if (after == 0) {
                    C = calculate_operator(operator_string, calculate_operator(operator_string, D, current_delta_f),
                                           current_delta_f_1);
                } else {
                    C = calculate_operator(operator_string, D, current_delta_f);
                }

                D = neutral_f;
                break;
            case Semantic::FOUND_E: //
                if (after == 0) {
                    if (operators.at(aggregator_string)(calculate_operator(operator_string,
                                                                           calculate_operator(
                                                                               operator_string, D, current_delta_f),
                                                                           current_delta_f_1), R)) {
                        f[i].ptr = &ct[i];
                        at[i].setValue(0);
                        ct[i].ptr = &at[i + 1];
                    } else if (calculate_operator(operator_string,
                                                  calculate_operator(operator_string, D, current_delta_f),
                                                  current_delta_f_1) == R) {
                        f[i].ptr = &at[i + 1];
                        ct[i].ptr = &at[i + 1];
                        at[i].ptr = &at[i + 1];
                    } else if (operators.at(aggregator_string)(R, calculate_operator(operator_string,
                                                                   calculate_operator(
                                                                       operator_string, D, current_delta_f),
                                                                   current_delta_f_1))) {
                        f[i].setValue(0);
                        ct[i].setValue(0);
                        at[i].ptr = &at[i + 1];
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
                        f[i].ptr = &ct[i];
                        at[i].setValue(0);
                        ct[i].ptr = &at[i + 1];
                    } else if (calculate_operator(operator_string, D, current_delta_f) == R) {
                        f[i].ptr = &at[i + 1];
                        ct[i].ptr = &at[i + 1];
                        at[i].ptr = &at[i + 1];
                    } else if (operators.at(aggregator_string)(
                        R, calculate_operator(operator_string, D, current_delta_f))) {
                        f[i].setValue(0);
                        ct[i].setValue(0);
                        at[i].ptr = &at[i + 1];
                    } else {
                        continue;
                    }

                    R = aggregators.at(aggregator_string)(R, calculate_operator(operator_string, D, current_delta_f));

                    D = neutral_f;
                }

                break;
            case Semantic::IN:
                f[i].setValue(0);
                ct[i].ptr = &ct[i + 1];
                at[i].ptr = &at[i + 1];

                if (after == 0) {
                    C = calculate_operator(operator_string, C,
                                           calculate_operator(operator_string, D, current_delta_f_1));
                } else {
                    C = calculate_operator(operator_string, C,
                                           calculate_operator(operator_string, D, current_delta_f));
                }
                D = neutral_f;
                break;
            default: throw std::invalid_argument("Invalid Semantic::Letter value");
        }
    }

    const unsigned long n = series.size() - 1;

    if (operators.at(aggregator_string)(C, R)) {
        ct[n].setValue(1);
        at[n].setValue(0);
    } else if (C == R) {
        if (R == default_gf) {
            ct[n].setValue(0);
            at[n].setValue(0);
        } else {
            ct[n].setValue(1);
            at[n].setValue(1);
        }
    } else {
        ct[n].setValue(0);
        at[n].setValue(1);
    }

    cout << "at = [";
    for (auto at_i : at) {
        cout << at_i.getValue() << ", ";
    }
    cout << "]" << endl;

    cout << "ct = [";
    for (auto ct_i : ct) {
        cout << ct_i.getValue() << ", ";
    }
    cout << "]" << endl;

    cout << "f = [";
    for (auto f_i : f) {
        cout << f_i.getValue() << ", ";
    }
    cout << "]" << endl;

    cout << "result = " << aggregators.at(aggregator_string)(R, C) << endl;

    return {
        .at = at,
        .ct = ct,
        .f = f,
        .R = R,
        .C = C,
        .D = D,
        .result = aggregators.at(aggregator_string)(R, C)
    };
}
