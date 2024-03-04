make_minimum_required(VERSION 3.10)

project(TestCatflap)

find_package(GTest REQUIRED)

add_executable(test_catflap test_catflap.cpp)
target_link_libraries(test_catflap PRIVATE GTest::GTest GTest::Main)

enable_testing()
add_test(NAME TestCatflap COMMAND test_catflap)