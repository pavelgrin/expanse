file(GLOB SOURCES engine/*.cpp engine/**/*.cpp)
source_group(Sources FILES ${SOURCES})

add_library(${ENGINE_OBJ} OBJECT ${SOURCES})
target_include_directories(${ENGINE_OBJ} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_library(${ENGINE_LIB} STATIC)
target_link_libraries(${ENGINE_LIB} PUBLIC ${ENGINE_OBJ})
