#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>
#include <limits>

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

inline Feature to_feature(const std::string &feature) {
    if (feature == "one")    return One;
    if (feature == "width")  return Width;
    if (feature == "surface")return Surface;
    if (feature == "max")    return FMax;
    if (feature == "min")    return FMin;
    if (feature == "range")  return Range;
    throw std::invalid_argument(
        "Invalid feature value. Must be one of:\n - one\n - width\n - surface\n - max\n - min\n - range"
    );
}

inline Aggregator to_aggregator(const std::string &aggregator) {
    if (aggregator == "max") return Max;
    if (aggregator == "min") return Min;
    throw std::invalid_argument("Invalid aggregator value. Must be one of:\n - max\n - min");
}

inline std::string to_string(const Feature feature) {
    switch (feature) {
        case One:    return "one";
        case Width:  return "width";
        case Surface:return "surface";
        case FMax:   return "max";
        case FMin:   return "min";
        case Range:  return "range";
        default:     throw std::invalid_argument("Invalid feature value");
    }
}

inline std::string to_string(const Aggregator aggregator) {
    switch (aggregator) {
        case Max: return "max";
        case Min: return "min";
        default:  throw std::invalid_argument("Invalid aggregator value");
    }
}

struct FeatureValues {
    double neutral;      ///< Neutral value (p. ex. 0)
    double min_f;        ///< Min limit of the feature
    double max_f;        ///< Max limit of the feature
    std::string phi;     ///< Operator (e.g. "+" or  "max" / "min")
    double delta;        ///< Associated delta (p. ex. -1 ou 1)
};

class Generator {
private:
    const std::map<Feature, FeatureValues> features = {
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
            {0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), "+", -1}
        },
        {
            FMax,
            {
                static_cast<double>(std::numeric_limits<int>::min()),
                static_cast<double>(std::numeric_limits<int>::min()),
                static_cast<double>(std::numeric_limits<int>::max()),
                "max", -1
            }
        },
        {
            FMin,
            {
                static_cast<double>(std::numeric_limits<int>::max()),
                static_cast<double>(std::numeric_limits<int>::min()),
                static_cast<double>(std::numeric_limits<int>::max()),
                "min", -1
            }
        },
        {
            Range,
            {0, 0, static_cast<double>(std::numeric_limits<int>::max()), "", -1}
        }
    };

    Feature feature;             ///< Feature chosen
    Aggregator aggregator;       ///< Aggregator chosen
    std::string pattern;         ///< Pattern chosen
    std::vector<int> series;     ///< Integers Series
    bool evaluate_performance;   ///< Boolean to indicate if we want to evaluate the performance

    [[nodiscard]] double get_default_gf() const;

    static std::string convert_to_code(int value);

    void update_main(const std::string &function_name) const;

    std::string generate_function_code(const std::string &aggregator_name,
                                       const std::string &feature_name,
                                       const std::string &pattern,
                                       const std::string &operator_string,
                                       double default_gf,
                                       double neutral_f);

public:
    Generator(Feature feature,
              Aggregator aggregator,
              std::string pattern,
              const std::vector<int>& series,
              bool evaluate_performance = false);

    explicit Generator(std::string pattern, const std::vector<int>& series, bool evaluate_performance = false);

    void generate();

    void generate_anomaly_detection();

    static long getCurrentMemoryUsageKB();
};

#endif // GENERATOR_H