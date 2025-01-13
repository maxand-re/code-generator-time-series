#include <iostream>
#include <vector>
#include "../lib/decoration/Decoration.h"
#include "../lib/generator/Generator.h"
#include "min_min_gorge.hpp"

#include "min_width_zigzag.hpp"
#include "max_width_zigzag.hpp"
#include "max_min_zigzag.hpp"
#include "max_max_peak.hpp"
#include "min_min_peak.hpp"
#include "min_max_peak.hpp"
#include "min_width_peak.hpp"
int main() {
    const vector<int> series = {1, 7, 3, 4, 4, 5, 5, 4, 2, 2, 6, 5, 4, 6, 5, 7};
    map<string, Decoration::Result*> results;

    auto result_min_min_gorge = min_min_gorge(series);
    Decoration::print_result(result_min_min_gorge, "min_min_gorge");
    results.insert({ "min_min_gorge", result_min_min_gorge });

    const vector<int> series2 ={4, 1, 3, 1, 4, 6, 1, 5, 5, 2, 7, 2, 3, 1, 6, 1};

    auto result_min_width_zigzag = min_width_zigzag(series2);
    Decoration::print_result(result_min_width_zigzag, "min_width_zigzag");
    results.insert({ "min_width_zigzag", result_min_width_zigzag });

    auto result_max_width_zigzag = max_width_zigzag(series);
    Decoration::print_result(result_max_width_zigzag, "max_width_zigzag");
    results.insert({ "max_width_zigzag", result_max_width_zigzag });

    auto result_max_min_zigzag = max_min_zigzag(series);
    Decoration::print_result(result_max_min_zigzag, "max_min_zigzag");
    results.insert({ "max_min_zigzag", result_max_min_zigzag });

    const vector<int> series3 = {7, 5, 5, 1, 4, 5, 2, 2, 3, 5, 6, 2, 3, 3, 3, 1};

    auto result_max_max_peak = max_max_peak(series3);
    Decoration::print_result(result_max_max_peak, "max_max_peak");
    results.insert({ "max_max_peak", result_max_max_peak });

    auto result_min_min_peak = min_min_peak(series3);
    Decoration::print_result(result_min_min_peak, "min_min_peak");
    results.insert({ "min_min_peak", result_min_min_peak });

    auto result_min_max_peak = min_max_peak(series3);
    Decoration::print_result(result_min_max_peak, "min_max_peak");
    results.insert({ "min_max_peak", result_min_max_peak });

    auto result_min_width_peak = min_width_peak(series3);
    Decoration::print_result(result_min_width_peak, "min_width_peak");
    results.insert({ "min_width_peak", result_min_width_peak });

    // End
    auto anomalies = Decoration::detect_anomalies(results);
    Decoration::print_anomalies(anomalies);

    return 0;
}
