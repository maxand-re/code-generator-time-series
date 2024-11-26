#include <vector>

#include "../lib/decoration/Decoration.h"

inline Decoration::Result* min_max_zigzag(std::vector<int> series) {
    int default_gf = std::numeric_limits<int>::max();
    int neutral_f = std::numeric_limits<int>::min();
    int delta_f = -1;

    string operator_string = "max";
    string aggregator_name = "min";
    string pattern = "zigzag";

    return Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, operator_string, aggregator_name, pattern);
}
