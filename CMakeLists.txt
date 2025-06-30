cmake_minimum_required(VERSION 3.16)
project(coolmd C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

# Create your library (remove test files from here)
add_library(coolmd STATIC
        parser.h
        parser.c
        tokenizer.h
        tokenizer.c
        merge.c
        merge.h
)

# Make headers available to other targets
target_include_directories(coolmd PUBLIC .)

# Add tests subdirectory
add_subdirectory(Tests)