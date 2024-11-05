#include <iostream>
#include <stdexcept>
#include "generator/Generator.h"
#include "transducers/Transducer.h"

void print_help() {
    std::cout <<
            "Usage: ./generate_code --pattern <pattern_name> --feature <feature_type> --aggregator <aggregator_type>\n";
    std::cout << "Options:\n";
    std::cout << "  --pattern       Specify the pattern to analyze (e.g., peak, plateau, zigzag, ...)\n";
    std::cout << "  --feature       Specify the feature to compute (e.g., one, width, surface, max, min, range)\n";
    std::cout << "  --aggregator    Specify the aggregator to compute (e.g., min, max, sum)\n";
}

int main(const int argc, char *argv[]) {
    std::string pattern_raw;
    std::string feature_raw;
    std::string aggregator_raw;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--pattern" && i + 1 < argc) {
            pattern_raw = argv[++i];
        } else if (arg == "--feature" && i + 1 < argc) {
            feature_raw = argv[++i];
        } else if (arg == "--aggregator" && i + 1 < argc) {
            aggregator_raw = argv[++i];
        } else if (arg == "--help") {
            print_help();
            return 0;
        } else {
            std::cerr << "Unknown argument: " << arg << "\n";
            print_help();
            return 1;
        }
    }

    if (pattern_raw.empty() || feature_raw.empty() || aggregator_raw.empty()) {
        std::cerr << "Error: --pattern, --feature, and --aggregator arguments are required.\n";
        print_help();
        return 1;
    }

    try {
        Feature feature = to_feature(feature_raw);
        Aggregator aggregator = to_aggregator(aggregator_raw);

        Generator generator{feature, aggregator, pattern_raw};
        generator.generate();
    } catch (const std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
