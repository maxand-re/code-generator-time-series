#include "Generator.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

Generator::Generator(Feature feature, Aggregator aggregator, const std::string &pattern)
    : feature(feature), aggregator(aggregator), pattern(pattern) {
}

int Generator::get_default_gf() const {
    switch (aggregator) {
        case Max: return this->features.at(this->feature).min_f;
        case Min: return this->features.at(this->feature).max_f;
        case Sum: return 0;
        default: return -1;
    }
}

std::string Generator::generate_function_code(const std::string &function_name, double default_gf, double neutral_f) {
    std::ofstream file("generated_" + function_name + ".cpp");
    std::stringstream ss;
    ss << "#include <vector>\n"
        << "\n"
        << "void " << function_name << "(std::vector<int> series) {\n"
        << "    double default_gf = " << default_gf << ";\n"
        << "    double neutral_f = " << neutral_f << ";\n"
        << "\n"
        << "    Decoration::apply_decorator(series, default_gf, neutral_f);\n"
        << "}\n";

    file << ss.str();
    file.close();

    return ss.str();
}

void Generator::generate() const {
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

    auto neutral_f = this->features.at(this->feature).neutral;

    string function_name = to_string(this->aggregator) + "_" + to_string(this->feature) + "_" + this->pattern;
    string code = generate_function_code(function_name, default_gf, neutral_f);

    std::cout << code << std::endl;
}
