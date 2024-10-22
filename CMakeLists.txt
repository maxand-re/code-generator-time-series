cmake_minimum_required(VERSION 3.29)
project(generate_code)

set(CMAKE_CXX_STANDARD 26)

add_executable(generate_code
        src/main.cpp
        src/transducers/SeedTransducer.cpp
        src/transducers/SeedTransducer.cpp
        src/transducers/SeedTransducer.h
        src/transducers/PlateauTransducer.cpp
        src/transducers/PlateauTransducer.h
)
