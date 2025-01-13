# Code generator for Time Series and Anomaly Detection

This project implements a code generator for time series analysis, aiming to detect anomalies within time series data. 
The tool generates code in C++ and applies structural constraints on time series data using finite transducers.
# Requirements
Cmake 3.10 or higher:
```zsh
sudo apt-get install cmake
```
or 
```zsh
brew install cmake
```

and nlohmann-json library
```zsh
brew install nlohmann-json
```

# Build
To build the project, execute the following commands:
```zsh
cmake .
make
```
# Usage
This tools requires nlohmann-json library. See here to install it: [nlohmann-json](https://github.com/nlohmann/json)

First, go to build directory and run cmake:
```zsh
cd build
cmake .
```

Then, execute the generate code command for a given pattern, feature, aggregator and series e.g., peak, max, max, {1,2,3,4,5,6,7,8,9,10}:
```zsh
./generate_code --pattern peak --feature max --aggregator max --series {1,2,3,4,5,6,7,8,9,10}
```
To detect anomalies first a specific pattern, execute the following, e.g. peak:
```zsh
./generate_code --pattern peak --detect-anomaly
```
To evaluate the performance of the code generator, execute the following:
```zsh
./generate_code --pattern peak --evaluate-performance
```
Then make sure to modify the series value, it could be a large random series with integers between 1 to 100: 
```c++
std::vector<int> series(100000);

std::random_device rd;
std::mt19937 gen(rd());
for (int i = 0; i < 100001; i++) {
    // randomly between 1 and 100
    std::uniform_int_distribution<> dis(1, 100);
    series[i] = dis(gen);
}
```

The parameters are:
- **--pattern**: the pattern to detect, e.g., peak, valley, etc.
- **--feature**: the feature to detect, e.g., max, min, etc.
- **--aggregator**: the aggregator to use, e.g., max, min, etc.
- **--detect-anomaly**: whether to detect anomalies or not.
- **--series**: the series to analyze, e.g., {1,2,3,4,5,6,7,8,9,10}.
- **--evaluate-performance**: whether to evaluate the performance of the code generator or not.
- **--help**: to display the help message.

## Performance Analysis

### Testing Methodology
We use this command:
```zsh
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
```c++
std::vector<int> series(100000);

std::random_device rd;
std::mt19937 gen(rd());
for (int i = 0; i < 100001; i++) {
    // randomly between 1 and 100
    std::uniform_int_distribution<> dis(1, 100);
    series[i] = dis(gen);
}
```

# Decoration Table
![transducer](/.github/images/transducer.png)
# Constraint Table
![constraint](/.github/images/constraint.png)

# References
- Beldiceanu, N., et al. Using Finite Transducers for Describing and Synthesising Structural Time-Series Constraints, Constraints Journal, 2015.
- Constraint Catalog: [Global Constraint Catalog](https://arxiv.org/abs/1609.08925)
