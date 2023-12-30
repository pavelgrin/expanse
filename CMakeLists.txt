cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MIMIC VERSION 0.1.0)

message("[BUILD_TYPE] ${CMAKE_BUILD_TYPE}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(NoInSourceBuilds)
CheckNoInSourceBuilds()

include(SharedTargets)

add_subdirectory(src bin)
add_subdirectory(test)
