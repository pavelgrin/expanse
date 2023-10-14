set(TARGET_OBJ engine_object)
set(TARGET_LIB engine)

file(GLOB SOURCES engine/*.cpp engine/**/*.cpp)
source_group(Sources FILES ${SOURCES})

add_library(${TARGET_OBJ} OBJECT ${SOURCES})
target_include_directories(${TARGET_OBJ} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_library(${TARGET_LIB} STATIC)
target_link_libraries(${TARGET_LIB} PUBLIC ${TARGET_OBJ})
