add_subdirectory(engine)
add_subdirectory(world)

# target_link_libraries(world_static engine_static)

add_executable(app main.cpp)
target_link_libraries(app  PRIVATE engine world)

include(build_info)
BindBuildInfo(app)
