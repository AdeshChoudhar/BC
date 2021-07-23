cmake_minimum_required(VERSION 3.19)
project(BC C)

set(CMAKE_C_STANDARD 11)

add_executable(BC main.c number.c number.h helpers.c helpers.h stack.c stack.h function.c function.h)