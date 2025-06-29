add_executable(parsertest ParserTests.cpp)

# Link against Google Test and your library
target_link_libraries(parsertest gtest gtest_main coolmd)

# Register the test with CTest
include(GoogleTest)
gtest_discover_tests(parsertest)