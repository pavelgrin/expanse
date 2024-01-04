add_executable(world_test world_test.cpp)
target_link_libraries(world_test PRIVATE ${WORLD_LIB})

AddTests(world_test)
