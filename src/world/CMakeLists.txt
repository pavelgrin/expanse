cmake_minimum_required(VERSION 3.16)

set(TARGET world)

file(GLOB SOURCES *.cpp **/*.cpp)
file(GLOB HEADERS *.hpp **/*.hpp)

source_group(Sources FILES ${SOURCES} ${HEADERS})

add_library(${TARGET} ${SOURCES} ${HEADERS})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
