#include <iostream>
#include <sstream>
#include <stdexcept>
#include "lib/generator/Generator.h"

using namespace std;

void print_help() {
    cout <<
            "Usage: ./generate_code --pattern <pattern_name> --feature <feature_type> --aggregator <aggregator_type>\n";
    cout << "Options:\n";
    cout << "  --pattern               Specify the pattern to analyze (e.g., peak, plateau, zigzag, ...)\n";
    cout << "  --feature               Specify the feature to compute (e.g., one, width, surface, max, min, range)\n";
    cout << "  --aggregator            Specify the aggregator to compute (e.g., min, max, sum)\n";
    cout << "  --detect-anomaly        Create an anomaly detector for the given pattern (--pattern)\n";
    cout << "  --evaluate-performance  Measure the performance of the generated code\n";
    cout << "  --series                Specify the series to analyze (e.g. 1,2,3,4,5)\n";
    cout << "  --help                  Print this help message\n";
}

int main(const int argc, char *argv[]) {
    string pattern_raw;
    string feature_raw;
    string aggregator_raw;
    vector<int> series = {};
    bool detect_anomaly = false;
    bool evaluate_performance = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "--pattern" && i + 1 < argc) {
            pattern_raw = argv[++i];
        } else if (arg == "--feature" && i + 1 < argc) {
            feature_raw = argv[++i];
        } else if (arg == "--aggregator" && i + 1 < argc) {
            aggregator_raw = argv[++i];
        } else if (arg == "--series" && i + 1 < argc) {
            string series_str = argv[++i];
            if (series_str.front() == '[' && series_str.back() == ']') {
                series_str = series_str.substr(1, series_str.size() - 2);
            }
            istringstream iss(series_str);
            int number;
            while (iss >> number) {
                series.push_back(number);
                if (iss.peek() == ',') {
                    iss.ignore();
                }
            }
        } else if (arg == "--detect-anomaly") {
            detect_anomaly = true;
        } else if (arg == "--evaluate-performance") {
            evaluate_performance = true;
        } else if (arg == "--help") {
            print_help();
            return 0;
        } else {
            cerr << "Unknown argument: " << arg << "\n";
            print_help();
            return 1;
        }
    }

    if (detect_anomaly && !pattern_raw.empty()) {
        try {
            Generator generator{pattern_raw, series, evaluate_performance};
            generator.generate_anomaly_detection();
        } catch (const invalid_argument &e) {
            cerr << "Error: " << e.what() << "\n";
            return 1;
        }
        return 0;
    }

    if (pattern_raw.empty() || feature_raw.empty() || aggregator_raw.empty()) {
        cerr << "Error: --pattern, --feature, and --aggregator arguments are required.\n";
        print_help();
        return 1;
    }

    try {
        Feature feature = to_feature(feature_raw);
        Aggregator aggregator = to_aggregator(aggregator_raw);

        Generator generator{feature, aggregator, pattern_raw, series, evaluate_performance};
        generator.generate();
    } catch (const invalid_argument &e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
