#pragma once

#include <vector>
#include "../lib/decoration/Decoration.h"
#include "../lib/generator/Generator.h"

inline Decoration::Result* min_width_zigzag(const std::vector<int>& series) {
    int default_gf = -1;
    int neutral_f = 0;
    int delta_f = 1;

    std::string operator_string = "+";
    std::string aggregator_name = "min";
    std::string pattern = "zigzag";

    return Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, operator_string, aggregator_name, pattern);
}
