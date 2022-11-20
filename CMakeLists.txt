cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(MIMIC)

set(CMAKE_BUILD_TYPE "Release")

set(APP_NAME app)

set(SOURCE
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/engine/engine.cpp"
)

add_executable("${APP_NAME}" "${SOURCE}")
set_target_properties("${APP_NAME}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
