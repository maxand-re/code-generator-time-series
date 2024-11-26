#include "generated/generated_max_max_peak.hpp"
#include "generated/generated_min_width_peak.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {
    std::vector<int> series = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Detection d'anomalie
    auto result_min_width = min_width_peak(series);
    auto result_max_max = max_max_peak(series);

    for (auto i = 0; i < series.size(); i++) {
        cout << result_max_max->f[i].getValue() << endl;
        cout << result_min_width->f[i].getValue() << endl;
        if (result_max_max->f[i].getValue() == 1 && result_min_width->f[i].getValue() == 1) {
            cout << "Anomalie : position : " << i << " | valeur : " << series[i] << endl;
        }
    }
*/
    return 0;
}
