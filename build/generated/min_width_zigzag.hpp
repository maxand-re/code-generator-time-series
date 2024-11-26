#include <vector>

#include "../lib/decoration/Decoration.h"

inline Decoration::Result* min_width_zigzag(std::vector<int> series) {
    int default_gf = -1;
    int neutral_f = 0;
    int delta_f = 1;

    string operator_string = "+";
    string aggregator_name = "min";
    string pattern = "zigzag";

    return Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, operator_string, aggregator_name, pattern);
}
