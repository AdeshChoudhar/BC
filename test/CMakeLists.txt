cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        test main.cpp
        ../src/functions.cpp ../src/functions.h
        ../src/Digit.cpp ../src/Digit.h
        ../src/Number.cpp ../src/Number.h
)
target_link_libraries(test gtest)
