add_executable(tokenizertest TokenizerTests.cpp)

# Link against Google Test and your library
target_link_libraries(tokenizertest
        PRIVATE
        gtest
        gtest_main
        coolmd
)

# Register the test with CTest
include(GoogleTest)
gtest_discover_tests(tokenizertest)