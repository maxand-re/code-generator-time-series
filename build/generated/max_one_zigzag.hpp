#include <vector>

#include "../lib/decoration/Decoration.h"

inline Decoration::Result* max_one_zigzag(std::vector<int> series) {
    int default_gf = 1;
    int neutral_f = 1;
    int delta_f = 0;

    string operator_string = "max";
    string aggregator_name = "max";
    string pattern = "zigzag";

    return Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, operator_string, aggregator_name, pattern);
}
