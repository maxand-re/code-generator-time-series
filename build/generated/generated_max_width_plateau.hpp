#include <vector>

#include "../lib/decoration/Decoration.h"

inline void max_width_plateau(std::vector<int> series) {
    int default_gf = 0;
    int neutral_f = 0;
    int delta_f = 1;

    string operator_string = "+";
    string aggregator_name = "max";
    string pattern = "plateau";

    Decoration::apply_decorator(series, default_gf, neutral_f, delta_f, operator_string, aggregator_name, pattern);
}
