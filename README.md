# Code generator for Time Series and Anomaly Detection

This project implements a code generator for time series analysis, aiming to detect anomalies within time series data. 
The tool generates code in C++ and applies structural constraints on time series data using finite transducers.
# Requirements
Cmake 3.10 or higher:
```
sudo apt-get install cmake
```
or 
```
brew install cmake
```

# Build
To build the project, execute the following commands:
```
cmake .
make
```
# Usage
This tools requires nlohmann-json library. See here to install it: [nlohmann-json](https://github.com/nlohmann/json)

First, go to build directory:
```
cd build
```

Then, execute the generate code command for a given pattern, feature, aggregator and series e.g., peak, max, max, {1,2,3,4,5,6,7,8,9,10}:
```
./generate_code --pattern peak --feature max --aggregator max --series {1,2,3,4,5,6,7,8,9,10}
```
To detect anomalies first a specific pattern, execute the following, e.g. peak:
```
./generate_code --pattern peak --detect-anomaly
```
The parameters are:
- pattern: the pattern to detect, e.g., peak, valley, etc.
- feature: the feature to detect, e.g., max, min, etc.
- aggregator: the aggregator to use, e.g., max, min, etc.
- detect-anomaly: whether to detect anomalies or not.
- series: the series to analyze, e.g., {1,2,3,4,5,6,7,8,9,10}.
- help: to display the help message.

## Performance Analysis

### Testing Methodology
The performance testing was conducted using the following setup:
- Input size: 1000 integers
- Value range: 1-100 (uniform distribution)
- Number of iterations: 100 runs
- Timing precision: microseconds
- Random number generation: Mersenne Twister (mt19937)

### Implementation Details
The performance measurement implementation leverages C++'s `std::chrono` library for high-precision timing:
```cpp
auto start = std::chrono::high_resolution_clock::now();
min_width_peak(series);
auto stop = std::chrono::high_resolution_clock::now();
```

To ensure reliable results, the testing procedure:
1. Generates a new random sequence for each iteration
2. Measures execution time using high-resolution clock
3. Calculates the average execution time across all runs

### Results

| Name           | Average time |
|----------------|--------------|
| min_width_peak | 3.964ms      |
| max_max_peak   | 4.021ms      |
| min_max_peak   | 4.026ms      |
|                |              |
|                |              |


# Transducers and Constraints
![transducer](/.github/images/transducer.png)
![constraint](/.github/images/constraint.png)

# References
- Beldiceanu, N., et al. Using Finite Transducers for Describing and Synthesising Structural Time-Series Constraints, Constraints Journal, 2015.
- Constraint Catalog: [Global Constraint Catalog](https://arxiv.org/abs/1609.08925)
