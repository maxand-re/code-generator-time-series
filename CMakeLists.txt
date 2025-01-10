cmake_minimum_required(VERSION 3.29)
project(generate_code)

set(CMAKE_CXX_STANDARD 26)

find_package(nlohmann_json 3.2.0 REQUIRED)

# Set the build directory outside cmake-build-debug
set(BUILD_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

# Compilation de l'exécutable principal
add_executable(generate_code
        src/main.cpp
        src/lib/Semantic.h
        src/lib/transducers/Transducer.cpp
        src/lib/transducers/Transducer.h
        src/lib/decoration/Decoration.cpp
        src/lib/decoration/Decoration.h
        src/lib/generator/Generator.cpp
        src/lib/generator/Generator.h
)
target_link_libraries(generate_code PRIVATE nlohmann_json::nlohmann_json)

# Copy necessary directories and files into the build directory
add_custom_command(TARGET generate_code POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources" "${BUILD_OUTPUT_DIR}/resources"
        COMMENT "Copying include files to build directory"
)

add_custom_command(TARGET generate_code POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/lib" "${BUILD_OUTPUT_DIR}/lib"
        COMMENT "Copying include files to build directory"
)
