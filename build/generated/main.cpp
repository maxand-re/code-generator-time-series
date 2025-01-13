#include <random>
#include <vector>
#include <__random/random_device.h>

#include "../lib/decoration/Decoration.h"
#include "../lib/generator/Generator.h"
#include "max_max_peak.hpp"
int main() {
    std::vector<int> series(100000);
    // Generate series
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < 100001; i++) {
        // randomly between 1 and 100
        std::uniform_int_distribution<> dis(1, 100);
        series[i] = dis(gen);
    }

    auto result_max_max_peak = max_max_peak(series);
    Decoration::print_result(result_max_max_peak, "max_max_peak");

    return 0;
}
