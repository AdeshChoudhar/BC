cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)

project(BC)

add_executable(
        BC main.cpp
        functions.cpp functions.h
        Digit.cpp Digit.h
        Number.cpp Number.h
)
