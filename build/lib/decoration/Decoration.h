#ifndef DECORATION_H
#define DECORATION_H

#include <vector>
#include <nlohmann/json.hpp>

using namespace std;

class Decoration {
public:
    struct Result {
        vector<int*> at;
        vector<int*> ct;
        vector<int*> f;
        int R;
        int C;
        int D;
        int result;
    };

    static nlohmann::json get_json(const string &pattern);

    static Result apply_decorator(const vector<int> &series,
                                int default_gf,
                                int neutral_f,
                                int delta_f,
                                const string &operator_string,
                                const string &aggregator_string,
                                const string &pattern);
};


#endif
