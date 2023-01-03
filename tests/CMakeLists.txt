set(test_sources
    fd_test.cpp)

find_package(Catch2 REQUIRED)
find_package(fmt REQUIRED)

add_executable(tests ${test_sources})
target_compile_features(tests PUBLIC cxx_std_20)
target_link_libraries(tests PUBLIC Catch2::Catch2WithMain fmt::fmt fd::fd)

target_compile_definitions(tests PUBLIC TEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test_data/")

add_test(NAME tests COMMAND tests)