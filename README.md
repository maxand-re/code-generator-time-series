# Code generator for Time Series and Anomaly Detection

This project implements a code generator for time series analysis, aiming to detect anomalies within time series data. 
The tool generates code in C++ and applies structural constraints on time series data using finite transducers.

# Usage
This tools requires nlohmann-json library. See here to install it: [nlohmann-json](https://github.com/nlohmann/json)

Execute the following command to generate code:
```
./generate_code --pattern peak --feature max --aggregator max
```
The parameters are:
- pattern: the pattern to detect, e.g., peak, valley, etc.
- feature: the feature to detect, e.g., max, min, etc.
- aggregator: the aggregator to use, e.g., max, min, etc.

# Transducers and Constraints
![transducer](/.github/images/transducer.png)
![constraint](/.github/images/constraint.png)

# References
- Beldiceanu, N., et al. Using Finite Transducers for Describing and Synthesising Structural Time-Series Constraints, Constraints Journal, 2015.
- Constraint Catalog: [Global Constraint Catalog](https://arxiv.org/abs/1609.08925)
