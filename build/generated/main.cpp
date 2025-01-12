#include <iostream>
#include <vector>
#include "../lib/decoration/Decoration.h"
#include "../lib/generator/Generator.h"
#include "min_one_peak.hpp"


#include "min_width_peak.hpp"
#include "min_surface_peak.hpp"
#include "min_max_peak.hpp"
#include "min_min_peak.hpp"
#include "min_range_peak.hpp"
#include "max_one_peak.hpp"
#include "max_width_peak.hpp"
#include "max_surface_peak.hpp"
#include "max_max_peak.hpp"
#include "max_min_peak.hpp"
#include "max_range_peak.hpp"
int main() {
    std::vector<int> series(1000);
    ranges::generate(series, []() { return rand() % 100 + 1; });
    map<string, Decoration::Result*> results;

    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_min_one_peak = min_one_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_min_one_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "min_one_peak", result_min_one_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_min_width_peak = min_width_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_min_width_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "min_width_peak", result_min_width_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_min_surface_peak = min_surface_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_min_surface_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "min_surface_peak", result_min_surface_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_min_max_peak = min_max_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_min_max_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "min_max_peak", result_min_max_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_min_min_peak = min_min_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_min_min_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "min_min_peak", result_min_min_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_min_range_peak = min_range_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_min_range_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "min_range_peak", result_min_range_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_max_one_peak = max_one_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_max_one_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "max_one_peak", result_max_one_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_max_width_peak = max_width_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_max_width_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "max_width_peak", result_max_width_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_max_surface_peak = max_surface_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_max_surface_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "max_surface_peak", result_max_surface_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_max_max_peak = max_max_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_max_max_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "max_max_peak", result_max_max_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_max_min_peak = max_min_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_max_min_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "max_min_peak", result_max_min_peak });
    }
    {
        using namespace std::chrono;
        auto mem_before = Generator::getCurrentMemoryUsageKB();
        auto start = high_resolution_clock::now();

        auto result_max_range_peak = max_range_peak(series);

        auto end = high_resolution_clock::now();
        auto mem_after = Generator::getCurrentMemoryUsageKB();
        auto elapsed_us = duration_cast<microseconds>(end - start).count();

        std::cout << "[Performance] result_max_range_peak : "
                  << elapsed_us << " µs, Memory diff = "
                  << (mem_after - mem_before) << " bytes" << std::endl;
        results.insert({ "max_range_peak", result_max_range_peak });
    }
    auto anomalies = Decoration::detect_anomalies(results);
    Decoration::print_anomalies(anomalies);

    return 0;
}
