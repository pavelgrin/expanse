add_executable(engine_test engine_test.cpp)
target_link_libraries(engine_test PRIVATE ${ENGINE_LIB})

AddTests(engine_test)
