#pragma once

#include <vector>
#include "../lib/decoration/Decoration.h"
#include "../lib/generator/Generator.h"

inline Decoration::Result* max_one_peak(std::vector<int> series) {
    int default_gf = 1;
    int neutral_f = 1;
    int delta_f = 0;

    std::string operator_string = "max";
    std::string aggregator_name = "max";
    std::string pattern = "peak";

    return Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, operator_string, aggregator_name, pattern);
}
