#ifndef DECORATION_H
#define DECORATION_H

#include <vector>
#include <nlohmann/json.hpp>

using namespace std;


class Node {
public:
    Node* ptr;
    std::optional<int> value;

    Node() : ptr(nullptr), value(std::nullopt) {}

    int getValue() {
        if (value.has_value()) {
            return value.value();
        }
        if (ptr) {
            return ptr->getValue();
        }
        throw std::runtime_error("No value defined in the node!");
    }

    void setValue(int val) {
        value = val;
    }

    Node& operator=(int value) {
        setValue(value);
        return *this;
    }

    Node& operator=(Node* ptr) {
        this->ptr = ptr;
        return *this;
    }
};

class Decoration {
public:
    struct Result {
        vector<Node> at;
        vector<Node> ct;
        vector<Node> f;
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
