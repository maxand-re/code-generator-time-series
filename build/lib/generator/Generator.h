#ifndef GENERATOR_H
#define GENERATOR_H
#include <map>
#include <string>
#include <stdexcept>

using namespace std;

enum Aggregator {
    Max,
    Min,
    Sum
};

enum Feature {
    One,
    Width,
    Surface,
    FMax,
    FMin,
    Range
};

inline Feature to_feature(const std::string &feature) {
    if (feature == "one") return One;
    if (feature == "width") return Width;
    if (feature == "surface") return Surface;
    if (feature == "max") return FMax;
    if (feature == "min") return FMin;
    if (feature == "range") return Range;
    throw std::invalid_argument(
        "Invalid feature value. Must be one of:\n - one\n - width\n - surface\n - max\n - min\n - range");
}

inline Aggregator to_aggregator(const std::string &aggregator) {
    if (aggregator == "max") return Max;
    if (aggregator == "min") return Min;
    if (aggregator == "sum") return Sum;
    throw std::invalid_argument("Invalid aggregator value. Must be one of:\n - max\n - min\n - sum");
}

inline std::string to_string(const Feature feature) {
    switch (feature) {
        case One: return "one";
        case Width: return "width";
        case Surface: return "surface";
        case FMax: return "max";
        case FMin: return "min";
        case Range: return "range";
        default: throw std::invalid_argument("Invalid feature value");
    }
}

inline std::string to_string(const Aggregator aggregator) {
    switch (aggregator) {
        case Max: return "max";
        case Min: return "min";
        case Sum: return "sum";
        default: throw std::invalid_argument("Invalid aggregator value");
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

    static string convert_to_code(double value);

    std::string generate_function_code(const std::string &aggregator_name, const std::string &feature_name,
                                              const std::string &pattern, const std::string &operator_string, double default_gf, double
                                              neutral_f);

    const std::map<Feature, FeatureValues> features = {
        {
            One, {1, 1, 1, "max", 0}
        },
        {
            Width, {0, 0, std::numeric_limits<double>::infinity(), "+", 1}
        },
        {
            Surface,
            {
                0, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), "+",
                -1
            }
        },
        {
            FMax,
            {
                -std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(),
                std::numeric_limits<double>::infinity(), "max", -1
            }
        },
        {
            FMin,
            {
                std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(),
                std::numeric_limits<double>::infinity(), "min", -1
            }
        },
        {
            Range, {0, 0, std::numeric_limits<double>::infinity(), "", -1}
        }
    };

    Feature feature;
    Aggregator aggregator;
    string pattern;

public:
    Generator(Feature feature, Aggregator aggregator, std::string pattern);

    void generate();
};


#endif
