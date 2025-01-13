#include <iostream>
#include <vector>
#include "../lib/decoration/Decoration.h"
#include "../lib/generator/Generator.h"
#include "min_one_peak.hpp"

#include "min_width_peak.hpp"
#include "min_surface_peak.hpp"
#include "min_max_peak.hpp"
#include "min_min_peak.hpp"
#include "min_range_peak.hpp"
#include "max_one_peak.hpp"
#include "max_width_peak.hpp"
#include "max_surface_peak.hpp"
#include "max_max_peak.hpp"
#include "max_min_peak.hpp"
#include "max_range_peak.hpp"
int main() {
    const vector<int> series = {1,2,3,4,3,2,1};
    map<string, Decoration::Result*> results;

    auto result_min_one_peak = min_one_peak(series);
    Decoration::print_result(result_min_one_peak, "min_one_peak");
    results.insert({ "min_one_peak", result_min_one_peak });

    auto result_min_width_peak = min_width_peak(series);
    Decoration::print_result(result_min_width_peak, "min_width_peak");
    results.insert({ "min_width_peak", result_min_width_peak });

    auto result_min_surface_peak = min_surface_peak(series);
    Decoration::print_result(result_min_surface_peak, "min_surface_peak");
    results.insert({ "min_surface_peak", result_min_surface_peak });

    auto result_min_max_peak = min_max_peak(series);
    Decoration::print_result(result_min_max_peak, "min_max_peak");
    results.insert({ "min_max_peak", result_min_max_peak });

    auto result_min_min_peak = min_min_peak(series);
    Decoration::print_result(result_min_min_peak, "min_min_peak");
    results.insert({ "min_min_peak", result_min_min_peak });

    auto result_min_range_peak = min_range_peak(series);
    Decoration::print_result(result_min_range_peak, "min_range_peak");
    results.insert({ "min_range_peak", result_min_range_peak });

    auto result_max_one_peak = max_one_peak(series);
    Decoration::print_result(result_max_one_peak, "max_one_peak");
    results.insert({ "max_one_peak", result_max_one_peak });

    auto result_max_width_peak = max_width_peak(series);
    Decoration::print_result(result_max_width_peak, "max_width_peak");
    results.insert({ "max_width_peak", result_max_width_peak });

    auto result_max_surface_peak = max_surface_peak(series);
    Decoration::print_result(result_max_surface_peak, "max_surface_peak");
    results.insert({ "max_surface_peak", result_max_surface_peak });

    auto result_max_max_peak = max_max_peak(series);
    Decoration::print_result(result_max_max_peak, "max_max_peak");
    results.insert({ "max_max_peak", result_max_max_peak });

    auto result_max_min_peak = max_min_peak(series);
    Decoration::print_result(result_max_min_peak, "max_min_peak");
    results.insert({ "max_min_peak", result_max_min_peak });

    auto result_max_range_peak = max_range_peak(series);
    Decoration::print_result(result_max_range_peak, "max_range_peak");
    results.insert({ "max_range_peak", result_max_range_peak });

    // End
    auto anomalies = Decoration::detect_anomalies(results);
    Decoration::print_anomalies(anomalies);

    return 0;
}
