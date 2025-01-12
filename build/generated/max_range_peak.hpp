#pragma once

#include <vector>
#include "../lib/decoration/Decoration.h"
#include "../lib/generator/Generator.h"

inline Decoration::Result* max_range_peak(std::vector<int> series) {
    int default_gf = 0;
    int neutral_f = 0;
    int delta_f = -1;

    std::string operator_string = "";
    std::string aggregator_name = "max";
    std::string pattern = "peak";

    return Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, operator_string, aggregator_name, pattern);
}
