#pragma once

#include <vector>
#include "../lib/decoration/Decoration.h"
#include "../lib/generator/Generator.h"

inline Decoration::Result* max_min_peak(std::vector<int> series) {
    int default_gf = numeric_limits<int>::min();
    int neutral_f = numeric_limits<int>::max();
    int delta_f = -1;

    std::string operator_string = "min";
    std::string aggregator_name = "max";
    std::string pattern = "peak";

    return Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, operator_string, aggregator_name, pattern);
}
