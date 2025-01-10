#include "Generator.h"

#include <fstream>
#include <ostream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <filesystem>
using namespace std;

Generator::Generator(const Feature feature, const Aggregator aggregator, string pattern, const vector<int> &series)
    : feature(feature), aggregator(aggregator), pattern(std::move(pattern)), series(series) {
}

Generator::Generator(string pattern) : feature(), aggregator(), pattern(std::move(pattern)) {
}

double Generator::get_default_gf() const {
    switch (aggregator) {
        case Max: return this->features.at(this->feature).min_f;
        case Min: return this->features.at(this->feature).max_f;
        default: return -1;
    }
}

string Generator::convert_to_code(const int value) {
    if (value == numeric_limits<int>::max()) {
        return "numeric_limits<int>::max()";
    }

    if (value == numeric_limits<int>::min()) {
        return "numeric_limits<int>::min()";
    }

    return to_string(value);
}

void Generator::update_main(const string &function_name) const {
    const string main_file_path = "generated/main.cpp";
    const string include_line = "#include \"" + function_name + ".hpp\"\n";
    const string call_line = "    auto result_" + function_name + " = " + function_name + "(series);\n";
    const string print_line = "    Decoration::print_result(result_" + function_name + ", \"" + function_name + "\");\n";
    const string push_result = "    results.insert({ \"" + function_name + "\", result_" + function_name + " });\n\n";

    stringstream new_series;
    new_series << "    const vector<int> series = {";
    for (size_t i = 0; i < this->series.size(); ++i) {
        new_series << this->series[i];
        if (i < this->series.size() - 1) {
            new_series << ", ";
        }
    }
    new_series << "};";

    ifstream existing_main(main_file_path);
    stringstream pre_main_content, post_main_content;

    if (existing_main.good()) {
        bool series_found = false;
        bool call_added = false;
        bool include_added = false;
        string line;
        bool inside_main = false;

        while (getline(existing_main, line)) {
            if (!inside_main && line.find("#include") != string::npos) {
                pre_main_content << line << "\n";
                if (line.find(function_name + ".hpp") != string::npos) {
                    include_added = true;
                }
            } else if (!inside_main && line.find("int main()") != string::npos) {
                inside_main = true;

                if (!include_added) {
                    pre_main_content << include_line;
                    include_added = true;
                }

                pre_main_content << line << "\n";
            } else if (inside_main) {
                if (line.find("const vector<int> series =") != string::npos) {
                    series_found = true;
                    post_main_content << (this->series.empty() ? line : new_series.str()) << "\n";
                } else if (line.find(function_name + "(series)") != string::npos) {
                    cout << "Warning: Function already generated." << endl;
                    call_added = true;
                    post_main_content << line << "\n";
                } else if (!call_added && line.find("auto anomalies = Decoration::detect_anomalies(results);") != string::npos) {
                    post_main_content << call_line << print_line << push_result;
                    call_added = true;
                    post_main_content << line << "\n";
                } else {
                    post_main_content << line << "\n";
                }
            } else {
                pre_main_content << line << "\n";
            }
        }

        if (!call_added) throw runtime_error("Failed to add calls inside main(). Check main.cpp structure.");
        if (!series_found && !this->series.empty()) post_main_content << new_series.str() << "\n";
    } else {
        // Create `main.cpp` if doesn't exist
        pre_main_content << "#include <iostream>\n"
                         << "#include <vector>\n"
                         << "#include \"../lib/decoration/Decoration.h\"\n"
                         << include_line << "\n\n";
        post_main_content << "int main() {\n"
                          << new_series.str() << "\n"
                          << "    map<string, Decoration::Result*> results;\n\n"
                          << call_line << print_line << push_result
                          << "    auto anomalies = Decoration::detect_anomalies(results);\n"
                          << "    Decoration::print_anomalies(anomalies);\n\n"
                          << "    return 0;\n"
                          << "}\n";
    }

    existing_main.close();

    ofstream updated_main(main_file_path);
    updated_main << pre_main_content.str();
    updated_main << post_main_content.str();
    updated_main.close();
}

string Generator::generate_function_code(
    const string &aggregator_name,
    const string &feature_name,
    const string &pattern,
    const string &operator_string,
    double default_gf,
    double neutral_f
) {
    const string function_name = aggregator_name + "_" + feature_name + "_" + pattern;

    ofstream file("generated/" + function_name + ".hpp");
    stringstream ss;
    ss << "#include <vector>\n\n"
            << "#include \"../lib/decoration/Decoration.h\"\n\n"
            << "inline Decoration::Result* " << function_name << "(vector<int> series) {\n"
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
    const vector aggregators = {Min, Max};

    const vector features = {One, Width, Surface, FMax, FMin, Range};

    for (const auto &agg: aggregators) {
        for (const auto &feat: features) {
            this->aggregator = agg;
            this->feature = feat;

            this->generate();
        }
    }
}
