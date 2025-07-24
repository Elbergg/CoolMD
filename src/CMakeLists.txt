cmake_minimum_required(VERSION 3.16)
project(coolmd C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Fetch Google Test


# Create your library (remove test files from here)
add_library(coolmd STATIC
        parser.h
        parser.c
        tokenizer.h
        tokenizer.c
        merge.c
        merge.h
        translator.h
        translator.c
        coolmd.h
        coolmd.c
)

# Make headers available to other targets
target_include_directories(coolmd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add tests subdirectory
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Fetch Google Test
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG main
    )
    FetchContent_MakeAvailable(googletest)

    # Add tests subdirectory
    add_subdirectory(Tests)
endif ()