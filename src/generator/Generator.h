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
    int get_default_gf() const;

    static std::string generate_function_code(const std::string &function_name, double default_gf, double neutral_f);

    std::map<Feature, FeatureValues> features = {
        {One, {1, 1, 1, "max", 0}},
        {Width, {0, 0, std::numeric_limits<double>::infinity(), "+", 1}},
        {
            Surface,
            {
                0, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), "+",
                std::numeric_limits<double>::quiet_NaN()
            }
        },
        {
            FMax,
            {
                -std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(),
                std::numeric_limits<double>::infinity(), "max", std::numeric_limits<double>::quiet_NaN()
            }
        },
        {
            FMin,
            {
                std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(),
                std::numeric_limits<double>::infinity(), "min", std::numeric_limits<double>::quiet_NaN()
            }
        },
        {Range, {0, 0, std::numeric_limits<double>::infinity(), "", std::numeric_limits<double>::quiet_NaN()}}
    };

    Feature feature;
    Aggregator aggregator;
    string pattern;

public:
    Generator(Feature feature, Aggregator aggregator, const std::string &pattern);

    void generate() const;
};


#endif
