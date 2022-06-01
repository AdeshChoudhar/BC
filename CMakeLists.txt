cmake_minimum_required(VERSION 3.20)
project(BC)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        BC src/main.cpp
        src/operations.cpp src/operations.h
        src/Digit.cpp src/Digit.h
        src/Number.cpp src/Number.h
)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        TEST test/main.cpp
        src/operations.cpp src/operations.h
        src/Digit.cpp src/Digit.h
        src/Number.cpp src/Number.h
)
target_link_libraries(TEST gtest)
