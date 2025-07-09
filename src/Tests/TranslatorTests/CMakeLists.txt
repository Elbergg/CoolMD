add_executable(translatortest TranslatorTests.cpp
        ../../translator.h
        ../../translator.c)

# Link against Google Test and your library
target_link_libraries(translatortest
        gtest
        gtest_main
        coolmd
)

# Register the test with CTest
include(GoogleTest)
gtest_discover_tests(translatortest)