cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MIMIC)

set(CMAKE_BUILD_TYPE Release)

set(TARGET_APP app)

set(SOURCE ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_executable(${TARGET_APP} ${SOURCE})
set_target_properties(${TARGET_APP} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/engine)
target_link_libraries(${TARGET_APP} engine)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/world)
target_link_libraries(${TARGET_APP} world)
