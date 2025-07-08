add_executable(tokenizertest TokenizerTests.cpp
        ../../merge.c
        ../../merge.h
        ../../translator.h
        ../../translator.c)

# Link against Google Test and your library
target_link_libraries(tokenizertest
        gtest
        gtest_main
        coolmd
)

# Register the test with CTest
include(GoogleTest)
gtest_discover_tests(tokenizertest)