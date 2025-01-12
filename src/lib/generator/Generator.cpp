#include "Generator.h"

#include <fstream>
#include <ostream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <sys/resource.h>
#include <unistd.h>

#include <nlohmann/json.hpp>

using namespace std;

Generator::Generator(const Feature feature,
                     const Aggregator aggregator,
                     std::string pattern,
                     const std::vector<int> &series,
                     bool evaluate_performance)
    : feature(feature),
      aggregator(aggregator),
      pattern(std::move(pattern)),
      series(series),
      evaluate_performance(evaluate_performance)
{
}

Generator::Generator(std::string pattern, const std::vector<int> &series, bool evaluate_performance)
    : feature(), aggregator(), pattern(std::move(pattern)), series(series),
      evaluate_performance(evaluate_performance)
{
}

long Generator::getCurrentMemoryUsageKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

double Generator::get_default_gf() const {
    switch (aggregator) {
        case Max: return this->features.at(this->feature).min_f;
        case Min: return this->features.at(this->feature).max_f;
        default:  return -1;
    }
}

std::string Generator::convert_to_code(const int value) {
    if (value == numeric_limits<int>::max()) {
        return "numeric_limits<int>::max()";
    }
    if (value == numeric_limits<int>::min()) {
        return "numeric_limits<int>::min()";
    }
    return to_string(value);
}

void Generator::update_main(const std::string &function_name) const {
    const string main_file_path = "generated/main.cpp";
    ifstream existing_main(main_file_path);

    const string include_line = "#include \"" + function_name + ".hpp\"\n";

    //  - Bloc without performance evaluation
    const string simple_call =
        "    auto result_" + function_name + " = " + function_name + "(series);\n";

    //  - Bloc with performance evaluation
    ostringstream perf_call;
    perf_call << "    {\n"
              << "        using namespace std::chrono;\n"
              << "        auto mem_before = Generator::getCurrentMemoryUsageKB();\n"
              << "        auto start = high_resolution_clock::now();\n\n"
              << "        auto result_" << function_name << " = " << function_name << "(series);\n\n"
              << "        auto end = high_resolution_clock::now();\n"
              << "        auto mem_after = Generator::getCurrentMemoryUsageKB();\n"
              << "        auto elapsed_us = duration_cast<microseconds>(end - start).count();\n\n"
              << "        std::cout << \"[Performance] result_" << function_name << " : \"\n"
              << "                  << elapsed_us << \" µs, Memory diff = \"\n"
              << "                  << (mem_after - mem_before) << \" Ko\" << std::endl;\n"
              << "        results.insert({ \"" + function_name + "\", result_" + function_name + " });\n"
              << "    }\n";

    const string call_insertion = this->evaluate_performance ? perf_call.str() : simple_call;

    const string push_result =
        "    results.insert({ \"" + function_name + "\", result_" + function_name + " });\n\n";

    // Construct series declaration
    stringstream new_series;
    new_series << "    const vector<int> series = {";
    for (size_t i = 0; i < this->series.size(); ++i) {
        new_series << this->series[i];
        if (i < this->series.size() - 1) {
            new_series << ", ";
        }
    }
    new_series << "};";

    stringstream pre_main_content, post_main_content;

    bool inside_main = false;
    bool include_added = false;
    bool series_found = false;
    bool call_inserted = false;

    if (existing_main.good()) {
        string line;
        while (getline(existing_main, line)) {
            // 1) If we are not in the int main()
            if (!inside_main) {
                if (line.find("#include") != string::npos) {
                    // Verify if we already have the include
                    if (line.find(function_name + ".hpp") != string::npos) {
                        include_added = true;
                    }
                    pre_main_content << line << "\n";
                }
                else if (line.find("int main()") != string::npos) {
                    inside_main = true;
                    if (!include_added) {
                        pre_main_content << include_line;
                        include_added = true;
                    }
                    pre_main_content << line << "\n";
                } else {
                    pre_main_content << line << "\n";
                }
            }
            // 2) If in main()
            else {
                if (line.find("const vector<int> series =") != string::npos) {
                    series_found = true;
                    // Update series if asked
                    if (!this->series.empty()) {
                        post_main_content << new_series.str() << "\n";
                    } else {
                        post_main_content << line << "\n";
                    }
                }
                // Prevent duplicated call to function_name(series)
                else if (line.find(function_name + "(series)") != string::npos) {
                    cerr << "[Warning] Function " << function_name << " is already in main.\n";
                    post_main_content << line << "\n";
                }
                else if (!call_inserted && line.find("auto anomalies = Decoration::detect_anomalies(results);") != string::npos) {
                    post_main_content << call_insertion;
                    if(!this->evaluate_performance) {
                        post_main_content << push_result;
                    }
                    call_inserted = true;
                    post_main_content << line << "\n";
                }
                else {
                    post_main_content << line << "\n";
                }
            }
        }

        if (!call_inserted) {
            throw runtime_error("Failed to add calls inside main(). 'auto anomalies' not found or parse error.");
        }

        if (!series_found && !this->series.empty()) {
            post_main_content << new_series.str() << "\n";
        }
    }
    else {
        // Case main.cpp doesn't exist
        pre_main_content << "#include <iostream>\n"
                         << "#include <vector>\n"
                         << "#include \"../lib/decoration/Decoration.h\"\n"
                         << "#include \"../lib/generator/Generator.h\"\n"
                         << include_line << "\n";

        post_main_content << "int main() {\n";
        if (!this->series.empty()) {
            post_main_content << new_series.str() << "\n";
        } else {
            post_main_content << "    const vector<int> series = {};\n";
        }
        post_main_content << "    map<string, Decoration::Result*> results;\n\n";

        post_main_content << call_insertion;

        if (!this->evaluate_performance) {
            post_main_content << push_result;
        }

        post_main_content
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

std::string Generator::generate_function_code(
    const std::string &aggregator_name,
    const std::string &feature_name,
    const std::string &pattern,
    const std::string &operator_string,
    double default_gf,
    double neutral_f
) {
    const std::string function_name = aggregator_name + "_" + feature_name + "_" + pattern;

    ofstream file("generated/" + function_name + ".hpp");
    stringstream ss;
    ss << "#pragma once\n\n"
       << "#include <vector>\n"
       << "#include \"../lib/decoration/Decoration.h\"\n"
       << "#include \"../lib/generator/Generator.h\"\n\n"
       << "inline Decoration::Result* " << function_name << "(std::vector<int> series) {\n"
       << "    int default_gf = " << convert_to_code(default_gf) << ";\n"
       << "    int neutral_f = " << convert_to_code(neutral_f) << ";\n"
       << "    int delta_f = " << this->features.at(feature).delta << ";\n\n"
       << "    std::string operator_string = \"" << operator_string << "\";\n"
       << "    std::string aggregator_name = \"" << aggregator_name << "\";\n"
       << "    std::string pattern = \"" << pattern << "\";\n\n"
       << "    return Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, "
          "operator_string, aggregator_name, pattern);\n"
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
    double neutral_f = this->features.at(this->feature).neutral;

    const std::string code = generate_function_code(
        to_string(aggregator),
        to_string(feature),
        pattern,
        this->features.at(this->feature).phi,
        default_gf,
        neutral_f
    );

    const std::string function_name = to_string(aggregator) + "_" + to_string(feature) + "_" + pattern;
    update_main(function_name);
}

void Generator::generate_anomaly_detection() {
    const std::vector<Aggregator> aggregators = {Min, Max};
    const std::vector<Feature> features = {One, Width, Surface, FMax, FMin, Range};

    for (auto agg : aggregators) {
        for (auto feat : features) {
            this->aggregator = agg;
            this->feature = feat;
            this->generate();
        }
    }
}