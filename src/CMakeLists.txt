add_subdirectory(engine)
add_subdirectory(world)

add_executable(app main.cpp)
target_link_libraries(app  PRIVATE ${ENGINE_LIB} ${WORLD_LIB})

include(BuildInfo)
BindBuildInfo(app)
