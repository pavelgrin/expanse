set(TARGET_OBJ world_object)
set(TARGET_LIB world)

file(GLOB SOURCES world/*.cpp world/**/*.cpp)
source_group(Sources FILES ${SOURCES})

add_library(${TARGET_OBJ} OBJECT ${SOURCES})
target_include_directories(${TARGET_OBJ} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
target_link_libraries(${TARGET_OBJ} PUBLIC engine)

add_library(${TARGET_LIB} STATIC ${SOURCES})
target_link_libraries(${TARGET_LIB} PUBLIC ${TARGET_OBJ})
