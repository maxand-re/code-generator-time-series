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

First, go to build directory and run cmake:
```
cd build
cmake .
```

Then, execute the generate code command for a given pattern, feature, aggregator and series e.g., peak, max, max, {1,2,3,4,5,6,7,8,9,10}:
```
./generate_code --pattern peak --feature max --aggregator max --series {1,2,3,4,5,6,7,8,9,10}
```
To detect anomalies first a specific pattern, execute the following, e.g. peak:
```
./generate_code --pattern peak --detect-anomaly
```
To evaluate the performance of the code generator, execute the following:
```
./generate_code --pattern peak --evaluate-performance
```
The parameters are:
- pattern: the pattern to detect, e.g., peak, valley, etc.
- feature: the feature to detect, e.g., max, min, etc.
- aggregator: the aggregator to use, e.g., max, min, etc.
- detect-anomaly: whether to detect anomalies or not.
- series: the series to analyze, e.g., {1,2,3,4,5,6,7,8,9,10}.
- evaluate-performance: whether to evaluate the performance of the code generator or not.
- help: to display the help message.

## Performance Analysis

### Testing Methodology
We use this command:
```
./generate_code --pattern peak --evaluate-performance
```
With that, we are able to evaluate the solving time and memory usage of each pattern / feature / aggregator combination. 
For our tests, we use the following parameters:
- Input size: 1000 integers
- Value range: 1-100
- Timing precision: microseconds
- Random number generation
- Multiple runs

Here are how we initialize the random series:
```
std::vector<int> series(1000);
ranges::generate(series, []() { return rand() % 100 + 1; });
```

# Transducers and Constraints
![transducer](/.github/images/transducer.png)
![constraint](/.github/images/constraint.png)

# References
- Beldiceanu, N., et al. Using Finite Transducers for Describing and Synthesising Structural Time-Series Constraints, Constraints Journal, 2015.
- Constraint Catalog: [Global Constraint Catalog](https://arxiv.org/abs/1609.08925)
