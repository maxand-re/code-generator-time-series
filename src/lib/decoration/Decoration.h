#ifndef DECORATION_H
#define DECORATION_H

#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <set>

using namespace std;

class Node {
public:
    Node* ptr;
    std::optional<int> value;

    Node() : ptr(nullptr), value(std::nullopt) {}
    explicit Node(int value) : ptr(nullptr), value(value) {}
    Node(const Node& other) {
        value = other.value;
        ptr = other.ptr ? new Node(*other.ptr) : nullptr;
    }

    int getValue() {
        if (ptr != nullptr) {
            return ptr->getValue();
        }
        if (value.has_value()) {
            return value.value();
        }
        return -1;
    }

    void setValue(int val) {
        value = val;
    }

    Node& operator=(int value) {
        setValue(value);
        return *this;
    }
};

class Decoration {
public:
    class Result {
    public:
        vector<Node> at;
        vector<Node> ct;
        vector<Node> f;
        int R, C, D, result_value;

        Result(const vector<Node>& at, const vector<Node>& ct, const vector<Node>& f,
               int R, int C, int D, int result_value)
            : at(at), ct(ct), f(f), R(R), C(C), D(D), result_value(result_value) {}
    };

    static void print_anomalies(const unordered_map<int, set<string>>& anomaly_map);

    static unordered_map<int, set<string>> detect_anomalies(const std::map<std::string, Result*>& result_map);

    static void print_result(const Result *result, const string &function_name);

    static nlohmann::json get_json(const string &pattern);

    static Result *apply_decorator(const vector<int> &series,
                                int default_gf,
                                int neutral_f,
                                int delta_f,
                                const string &operator_string,
                                const string &aggregator_string,
                                const string &pattern);
};


#endif
