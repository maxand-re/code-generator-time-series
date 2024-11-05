cmake_minimum_required(VERSION 3.29)
project(generate_code_build)

set(CMAKE_CXX_STANDARD 26)
find_package(nlohmann_json 3.2.0 REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/generated/*.hpp")

# RESOURCES
set(RESOURCES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")
set(RESOURCES_OUTPUT_DIR "${CMAKE_BINARY_DIR}/resources")

add_executable(generate_code_build
        lib/Semantic.h
        lib/transducers/Transducer.cpp
        lib/transducers/Transducer.h
        lib/decoration/Decoration.cpp
        lib/decoration/Decoration.h
        lib/generator/Generator.cpp
        lib/generator/Generator.h
        main.cpp
        ${SOURCE_FILES}
)

add_custom_command(
        OUTPUT ${RESOURCES_OUTPUT_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_SOURCE_DIR} ${RESOURCES_OUTPUT_DIR}
        DEPENDS ${RESOURCES_SOURCE_DIR}
        COMMENT "Copying resources folder to build directory"
)

add_custom_target(copy_resources ALL
        DEPENDS ${RESOURCES_OUTPUT_DIR}
)

add_dependencies(generate_code_build copy_resources)

target_link_libraries(generate_code_build PRIVATE nlohmann_json::nlohmann_json)