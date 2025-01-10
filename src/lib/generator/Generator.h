#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

using namespace std;

enum Aggregator {
    Max,
    Min
};

enum Feature {
    One,
    Width,
    Surface,
    FMax,
    FMin,
    Range
};

inline Feature to_feature(const string &feature) {
    if (feature == "one") return One;
    if (feature == "width") return Width;
    if (feature == "surface") return Surface;
    if (feature == "max") return FMax;
    if (feature == "min") return FMin;
    if (feature == "range") return Range;
    throw invalid_argument(
        "Invalid feature value. Must be one of:\n - one\n - width\n - surface\n - max\n - min\n - range");
}

inline Aggregator to_aggregator(const string &aggregator) {
    if (aggregator == "max") return Max;
    if (aggregator == "min") return Min;
    throw invalid_argument("Invalid aggregator value. Must be one of:\n - max\n - min");
}

inline string to_string(const Feature feature) {
    switch (feature) {
        case One: return "one";
        case Width: return "width";
        case Surface: return "surface";
        case FMax: return "max";
        case FMin: return "min";
        case Range: return "range";
        default: throw invalid_argument("Invalid feature value");
    }
}

inline string to_string(const Aggregator aggregator) {
    switch (aggregator) {
        case Max: return "max";
        case Min: return "min";
        default: throw invalid_argument("Invalid aggregator value");
    }
}

struct FeatureValues {
    double neutral;
    double min_f;
    double max_f;
    string phi;
    double delta;
};

class Generator {
    [[nodiscard]] double get_default_gf() const;

    static string convert_to_code(int value);

    void update_main(const string &function_name) const;

    string generate_function_code(const string &aggregator_name, const string &feature_name,
                                              const string &pattern, const string &operator_string, double default_gf, double
                                              neutral_f);

    const map<Feature, FeatureValues> features = {
        {
            One,
            {1, 1, 1, "max", 0}
        },
        {
            Width,
            {0, 0, -1, "+", 1}
        },
        {
            Surface,
            {0, numeric_limits<int>::min(), numeric_limits<int>::max(), "+",-1}
        },
        {
            FMax,
            {
                numeric_limits<int>::min(), numeric_limits<int>::min(),
                numeric_limits<int>::max(), "max", -1
            }
        },
        {
            FMin,
            {numeric_limits<int>::max(), numeric_limits<int>::min(), numeric_limits<int>::max(), "min", -1}
        },
        {
            Range, {0, 0, numeric_limits<int>::max(), "", -1}
        }
    };

    Feature feature;
    Aggregator aggregator;
    string pattern;
    vector<int> series;

public:
    Generator(Feature feature, Aggregator aggregator, string pattern, const vector<int>& series);
    explicit Generator(string pattern);

    void generate();
    void generate_anomaly_detection();
};


#endif
