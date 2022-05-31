cmake_minimum_required(VERSION 3.20)
project(BC)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        BC main.cpp
        functions.cpp functions.h
        Digit.cpp Digit.h
        Number.cpp Number.h
)

add_subdirectory(Testing)
add_executable(
        test Testing/main.cpp
        functions.cpp functions.h
        Digit.cpp Digit.h
        Number.cpp Number.h
)
target_link_libraries(test gtest)
