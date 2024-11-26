#include "Generator.h"

#include <fstream>
#include <ostream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <filesystem>

Generator::Generator(const Feature feature, const Aggregator aggregator, std::string pattern)
    : feature(feature), aggregator(aggregator), pattern(std::move(pattern)) {
}

Generator::Generator(std::string pattern) : feature(), aggregator(), pattern(std::move(pattern)) {
}

double Generator::get_default_gf() const {
    switch (aggregator) {
        case Max: return this->features.at(this->feature).min_f;
        case Min: return this->features.at(this->feature).max_f;
        case Sum: return 0;
        default: return -1;
    }
}

string Generator::convert_to_code(const int value) {
    if (value == std::numeric_limits<int>::max()) {
        return "std::numeric_limits<int>::max()";
    }

    if (value == std::numeric_limits<int>::min()) {
        return "std::numeric_limits<int>::min()";
    }

    return std::to_string(value);
}

void Generator::update_main(const std::string& function_name) {
    const std::string main_file_path = "generated/main.cpp";
    const std::string include_line = "#include \"" + function_name + ".hpp\"\n";
    const std::string call_line = "    auto result_" + function_name + " = " + function_name + "(series);\n";
    const std::string print_line = "    print_result(result_" + function_name + ", \"" + function_name + "\");\n";

    std::ifstream existing_main(main_file_path);
    bool main_exists = existing_main.good();
    std::stringstream main_content;

    if (main_exists) {
        bool include_added = false;
        bool inside_main = false;
        bool call_added = false;

        std::string line;
        while (std::getline(existing_main, line)) {
            if (!include_added && line.find("#include") != std::string::npos && line < include_line) {
                main_content << include_line;
                include_added = true;
            }

            if (line.find("int main()") != std::string::npos) {
                inside_main = true;
            }

            if (inside_main && !call_added && line.find("return 0;") != std::string::npos) {
                main_content << call_line;
                main_content << print_line;
                call_added = true;
            }

            main_content << line << "\n";
        }

        if (!include_added) main_content << include_line;
        if (!call_added) {
            throw std::runtime_error("Failed to add calls inside main(). Check main.cpp structure.");
        }
    } else {
        main_content << "#include <iostream>\n";
        main_content << "#include <vector>\n";
        main_content << "#include \"../lib/decoration/Decoration.h\"\n";
        main_content << include_line << "\n";
        main_content << "void print_result(const Decoration::Result* result, const string& function_name) {\n";
        main_content << "    cout << \"--------------\" << endl;\n";
        main_content << "    cout << \"Function: \" << function_name << endl;\n";
        main_content << "    cout << \"at = [\";\n";
        main_content << "    for (auto at_i : result->at) {\n";
        main_content << "        cout << at_i.getValue() << \", \";\n";
        main_content << "    }\n";
        main_content << "    cout << \"]\" << endl;\n";
        main_content << "    cout << \"ct = [\";\n";
        main_content << "    for (auto ct_i : result->ct) {\n";
        main_content << "        cout << ct_i.getValue() << \", \";\n";
        main_content << "    }\n";
        main_content << "    cout << \"]\" << endl;\n";
        main_content << "    cout << \"f = [\";\n";
        main_content << "    for (auto f_i : result->f) {\n";
        main_content << "        cout << f_i.getValue() << \", \";\n";
        main_content << "    }\n";
        main_content << "    cout << \"]\" << endl;\n";
        main_content << "    cout << \"result = \" << result->result_value << endl;\n";
        main_content << "    cout << \"--------------\" << endl;\n";
        main_content << "}\n";
        main_content << "\n";
        main_content << "int main() {\n";
        main_content << "    const std::vector<int> series = {}; /* Insert your serie here */\n";
        main_content << call_line;
        main_content << print_line;
        main_content << "    return 0;\n";
        main_content << "}\n";
    }

    existing_main.close();

    std::ofstream updated_main(main_file_path);
    updated_main << main_content.str();
    updated_main.close();
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

    std::ofstream file("generated/" + function_name + ".hpp");
    std::stringstream ss;
    ss << "#include <vector>\n\n"
            << "#include \"../lib/decoration/Decoration.h\"\n\n"
            << "inline Decoration::Result* " << function_name << "(std::vector<int> series) {\n"
            << "    int default_gf = " << convert_to_code(default_gf) << ";\n"
            << "    int neutral_f = " << convert_to_code(neutral_f) << ";\n"
            << "    int delta_f = " << this->features.at(feature).delta << ";\n\n"
            << "    string operator_string = \"" << operator_string << "\";\n"
            << "    string aggregator_name = \"" << aggregator_name << "\";\n"
            << "    string pattern = \"" << pattern << "\";\n"
            << "\n"
            << "    return Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, operator_string, aggregator_name, pattern);\n"
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
            break;
        case Sum:
            default_gf = 0;
            break;
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
    const string function_name = to_string(aggregator) + "_" + to_string(feature) + "_" + pattern;

    update_main(function_name);
}

void Generator::generate_anomaly_detection() {

}

