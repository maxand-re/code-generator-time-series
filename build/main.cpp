#include "generated/generated_max_max_peak.hpp"
#include "generated/generated_min_width_peak.hpp"
#include "generated/generated_min_max_peak.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <numeric>


int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    std::vector<int> series(1000);
    std::vector<long long> times;
    times.reserve(100);

    for(int test = 0; test < 100; test++) {
        for(int i = 0; i < 1000; i++) {
            series[i] = dis(gen);
            std::cout << series[i] << ',';
        }
        std::cout << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        min_max_peak(series);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        times.push_back(duration.count());

        std::cout << "Run " << test + 1 << " time: "
                  << duration.count() << " microseconds" << std::endl;
    }

    double average = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
    std::cout << "\nAverage time over " << times.size() << " runs: "
              << average << " microseconds" << std::endl;

    return 0;
}
