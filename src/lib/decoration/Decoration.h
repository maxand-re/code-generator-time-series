#ifndef DECORATION_H
#define DECORATION_H

#include <vector>
#include <nlohmann/json.hpp>

using namespace std;

class Decoration {
public:
    static nlohmann::json get_json(const string &pattern);

    static void apply_decorator(const vector<int> &series, double default_gf, double neutral_f,
                                int delta_f, const string &operator_string, const string &aggregator_string, const string &pattern);
};


#endif
