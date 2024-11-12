#include "Generator.h"

#include <fstream>
#include <ostream>
#include <sstream>
#include <nlohmann/json.hpp>

Generator::Generator(Feature feature, Aggregator aggregator, std::string pattern)
    : feature(feature), aggregator(aggregator), pattern(std::move(pattern)) {
}

double Generator::get_default_gf() const {
    switch (aggregator) {
        case Max: return this->features.at(this->feature).min_f;
        case Min: return this->features.at(this->feature).max_f;
        case Sum: return 0;
        default: return -1;
    }
}

string Generator::convert_to_code(const double value) {
    if (value == std::numeric_limits<double>::infinity()) {
        return "std::numeric_limits<double>::infinity()";
    }

    if (value == -std::numeric_limits<double>::infinity()) {
        return "-std::numeric_limits<double>::infinity()";
    }

    return std::to_string(value);
}

std::string Generator::generate_function_code(
    const std::string &aggregator_name,
    const std::string &feature_name,
    const std::string &pattern,
    const std::string &operator_string,
    double default_gf,
    double neutral_f
) {
    const string function_name = aggregator_name + "_" + feature_name + "_" + pattern;

    std::ofstream file("generated/generated_" + function_name + ".hpp");
    std::stringstream ss;
    ss << "#include <vector>\n\n"
            << "#include \"../lib/decoration/Decoration.h\"\n\n"
            << "inline void " << function_name << "(std::vector<int> series) {\n"
            << "    double default_gf = " << convert_to_code(default_gf) << ";\n"
            << "    double neutral_f = " << convert_to_code(neutral_f) << ";\n"
            << "    double delta_f = " << this->features.at(feature).delta << ";\n\n"
            << "    string operator_string = \"" << operator_string << "\";\n"
            << "    string aggregator_name = \"" << aggregator_name << "\";\n"
            << "    string pattern = \"" << pattern << "\";\n"
            << "\n"
            << "    Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, operator_string, aggregator_name, pattern);\n"
            << "}\n";

    file << ss.str();
    file.close();

    return ss.str();
}

void Generator::generate() {
    double default_gf = 0;
    switch (aggregator) {
        case Max:
            default_gf = this->features.at(this->feature).min_f;
            break;
        case Min:
            default_gf = this->features.at(this->feature).max_f;
        case Sum:
            default_gf = 0;
        default:
            throw runtime_error("The selected aggregator doesn't exist");
    }

    const auto neutral_f = this->features.at(this->feature).neutral;

    const string code = generate_function_code(
        to_string(aggregator),
        to_string(feature),
        pattern,
        this->features.at(this->feature).phi,
        default_gf,
        neutral_f
    );

    // std::cout << code << std::endl;
}
