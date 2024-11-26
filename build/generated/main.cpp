#include <iostream>
#include <vector>
#include "min_width_zigzag.hpp"
#include "min_surface_zigzag.hpp"
#include "min_range_zigzag.hpp"
#include "min_min_zigzag.hpp"
#include "min_max_zigzag.hpp"
#include "max_width_zigzag.hpp"
#include "max_surface_zigzag.hpp"
#include "max_range_zigzag.hpp"
#include "max_one_zigzag.hpp"
#include "max_min_zigzag.hpp"
#include "max_max_zigzag.hpp"
#include "../lib/decoration/Decoration.h"
#include "min_one_zigzag.hpp"


int main() {
    const std::vector<int> series = {4, 1, 3, 1, 4, 6, 1, 5, 5, 2, 7, 2, 3, 1, 6, 1}; /* Insert your serie here */
    std::map<std::string, Decoration::Result*> results;

    auto result_min_one_zigzag = min_one_zigzag(series);
    Decoration::print_result(result_min_one_zigzag, "min_one_zigzag");
    results.insert({ "min_one_zigzag", result_min_one_zigzag});

    auto result_min_width_zigzag = min_width_zigzag(series);
    Decoration::print_result(result_min_width_zigzag, "min_width_zigzag");
    results.insert({ "min_width_zigzag", result_min_width_zigzag});

    auto result_min_surface_zigzag = min_surface_zigzag(series);
    Decoration::print_result(result_min_surface_zigzag, "min_surface_zigzag");
    results.insert({ "min_surface_zigzag", result_min_surface_zigzag});

    auto result_min_max_zigzag = min_max_zigzag(series);
    Decoration::print_result(result_min_max_zigzag, "min_max_zigzag");
    results.insert({ "min_max_zigzag", result_min_max_zigzag});

    auto result_min_min_zigzag = min_min_zigzag(series);
    Decoration::print_result(result_min_min_zigzag, "min_min_zigzag");
    results.insert({ "min_min_zigzag", result_min_min_zigzag});

    auto result_min_range_zigzag = min_range_zigzag(series);
    Decoration::print_result(result_min_range_zigzag, "min_range_zigzag");
    results.insert({ "min_range_zigzag", result_min_range_zigzag});

    auto result_max_one_zigzag = max_one_zigzag(series);
    Decoration::print_result(result_max_one_zigzag, "max_one_zigzag");
    results.insert({ "max_one_zigzag", result_max_one_zigzag});

    auto result_max_width_zigzag = max_width_zigzag(series);
    Decoration::print_result(result_max_width_zigzag, "max_width_zigzag");
    results.insert({ "max_width_zigzag", result_max_width_zigzag});

    auto result_max_surface_zigzag = max_surface_zigzag(series);
    Decoration::print_result(result_max_surface_zigzag, "max_surface_zigzag");
    results.insert({ "max_surface_zigzag", result_max_surface_zigzag});

    auto result_max_max_zigzag = max_max_zigzag(series);
    Decoration::print_result(result_max_max_zigzag, "max_max_zigzag");
    results.insert({ "max_max_zigzag", result_max_max_zigzag});

    auto result_max_min_zigzag = max_min_zigzag(series);
    Decoration::print_result(result_max_min_zigzag, "max_min_zigzag");
    results.insert({ "max_min_zigzag", result_max_min_zigzag});

    auto result_max_range_zigzag = max_range_zigzag(series);
    Decoration::print_result(result_max_range_zigzag, "max_range_zigzag");
    results.insert({ "max_range_zigzag", result_max_range_zigzag});

    auto anomalies = Decoration::detect_anomalies(results);
    Decoration::print_anomalies(anomalies);

    return 0;
}
