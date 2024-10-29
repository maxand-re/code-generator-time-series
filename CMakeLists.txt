cmake_minimum_required(VERSION 3.29)
project(generate_code)

set(CMAKE_CXX_STANDARD 26)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(generate_code
        src/main.cpp
        src/Semantic.h
        src/transducers/Transducer.cpp
        src/transducers/Transducer.h
        src/decoration/Decoration.cpp
        src/decoration/Decoration.h
        src/generator/Generator.cpp
        src/generator/Generator.h
)

# RESOURCES
set(RESOURCES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")
set(RESOURCES_OUTPUT_DIR "${CMAKE_BINARY_DIR}/resources")

add_custom_command(
        OUTPUT ${RESOURCES_OUTPUT_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_SOURCE_DIR} ${RESOURCES_OUTPUT_DIR}
        DEPENDS ${RESOURCES_SOURCE_DIR}
        COMMENT "Copying resources folder to build directory"
)

add_custom_target(copy_resources ALL
        DEPENDS ${RESOURCES_OUTPUT_DIR}
)

add_dependencies(generate_code copy_resources)


target_link_libraries(generate_code PRIVATE nlohmann_json::nlohmann_json)