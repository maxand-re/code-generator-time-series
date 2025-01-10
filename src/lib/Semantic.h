#ifndef SEMANTIC_H
#define SEMANTIC_H
#include <string>

namespace Semantic {
    enum Letter {
        OUT,
        OUT_R,
        OUT_A,
        MAYBE_B,
        MAYBE_A,
        FOUND,
        FOUND_E,
        IN
    };

    inline Letter string_to_letter(const std::string &str) {
        if (str == "out") return OUT;
        if (str == "out_r") return OUT_R;
        if (str == "out_a") return OUT_A;
        if (str == "maybe_b") return MAYBE_B;
        if (str == "maybe_a") return MAYBE_A;
        if (str == "found") return FOUND;
        if (str == "found_e") return FOUND_E;
        if (str == "in") return IN;
        throw std::invalid_argument("Invalid string for Semantic::Letter");
    }

    inline std::string letter_to_string(Letter letter) {
        switch (letter) {
            case OUT: return "out";
            case OUT_R: return "out_r";
            case OUT_A: return "out_a";
            case MAYBE_B: return "maybe_b";
            case MAYBE_A: return "maybe_a";
            case FOUND: return "found";
            case FOUND_E: return "found_e";
            case IN: return "in";
            default: throw std::invalid_argument("Invalid Semantic::Letter value");
        }
    }
}


#endif
