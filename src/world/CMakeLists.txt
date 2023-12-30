file(GLOB SOURCES world/*.cpp world/**/*.cpp)
source_group(Sources FILES ${SOURCES})

add_library(${WORLD_OBJ} OBJECT ${SOURCES})
target_include_directories(${WORLD_OBJ} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
target_link_libraries(${WORLD_OBJ} PUBLIC ${ENGINE_LIB})

add_library(${WORLD_LIB} STATIC ${SOURCES})
target_link_libraries(${WORLD_LIB} PUBLIC ${WORLD_OBJ})

include(Coverage)
EnableCoverage(${WORLD_LIB})
CleanCoverage(${WORLD_LIB})
