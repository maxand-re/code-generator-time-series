#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include "lib/generator/Generator.h"

using namespace std;

void print_help() {
    cout << R"(
Usage: ./generate_code [OPTIONS]

Options:
  --pattern               Specify the pattern to analyze (e.g., peak, plateau, zigzag, ...)
  --feature               Specify the feature to compute (e.g., one, width, surface, max, min, range)
  --aggregator            Specify the aggregator to compute (e.g., min, max, sum)
  --detect-anomaly        Create an anomaly detector for the given pattern (--pattern required)
  --evaluate-performance  Measure the performance of the generated code
  --series                Specify the series to analyze (e.g., 1,2,3,4,5 or [1,2,3,4,5])
  --help                  Print this help message
)";
}

bool is_option_valid(const string &option) {
    const unordered_set<string> valid_options = {
        "--pattern", "--feature", "--aggregator", "--series",
        "--detect-anomaly", "--evaluate-performance", "--help"
    };
    return valid_options.count(option) > 0;
}

vector<int> parse_series(const string &series_str) {
    vector<int> series;
    string cleaned_series = series_str;

    // Remove square brackets if present
    if (cleaned_series.front() == '[' && cleaned_series.back() == ']') {
        cleaned_series = cleaned_series.substr(1, cleaned_series.size() - 2);
    }

    // Parse the numbers
    istringstream iss(cleaned_series);
    int number;
    while (iss >> number) {
        series.push_back(number);
        if (iss.peek() == ',') {
            iss.ignore();
        }
    }

    return series;
}

int main(const int argc, char *argv[]) {
    if (argc == 1) {
        cerr << "Error: No arguments provided.\n";
        print_help();
        return 1;
    }

    string pattern_raw;
    string feature_raw;
    string aggregator_raw;
    vector<int> series;
    bool detect_anomaly = false;
    bool evaluate_performance = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (!is_option_valid(arg)) {
            cerr << "Error: Unknown argument '" << arg << "'\n";
            print_help();
            return 1;
        }

        if (arg == "--pattern" && i + 1 < argc) {
            pattern_raw = argv[++i];
        } else if (arg == "--feature" && i + 1 < argc) {
            feature_raw = argv[++i];
        } else if (arg == "--aggregator" && i + 1 < argc) {
            aggregator_raw = argv[++i];
        } else if (arg == "--series" && i + 1 < argc) {
            try {
                series = parse_series(argv[++i]);
            } catch (const exception &) {
                cerr << "Error: Invalid series format. Example of valid series: [1,2,3,4] or 1,2,3,4\n";
                return 1;
            }
        } else if (arg == "--detect-anomaly") {
            detect_anomaly = true;
        } else if (arg == "--evaluate-performance") {
            evaluate_performance = true;
        } else if (arg == "--help") {
            print_help();
            return 0;
        }
    }

    // Handle specific cases
    if (detect_anomaly) {
        if (pattern_raw.empty()) {
            cerr << "Error: --detect-anomaly requires --pattern.\n";
            print_help();
            return 1;
        }

        try {
            Generator generator{pattern_raw, series, evaluate_performance};
            generator.generate_anomaly_detection();
        } catch (const invalid_argument &e) {
            cerr << "Error: " << e.what() << "\n";
            return 1;
        }
        return 0;
    }

    if (evaluate_performance) {
        if (pattern_raw.empty()) {
            cerr << "Error: --evaluate-performance requires --pattern.\n";
            print_help();
            return 1;
        }

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

    // Main case: Generating code with pattern, feature, and aggregator
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