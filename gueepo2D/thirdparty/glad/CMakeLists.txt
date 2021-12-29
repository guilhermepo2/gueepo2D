cmake_minimum_required(VERSION 3.10)

project(glad)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(glad
    include/glad/glad.h
    include/KHR/khrplatform.h
    src/glad.c
)

include_directories(include)