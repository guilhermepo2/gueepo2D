cmake_minimum_required(VERSION 3.10)
project(gueepo2D)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# this should be in a dependencies subproject
add_subdirectory(gueepo2D/thirdparty/glad)
add_subdirectory(gueepo2D/thirdparty/imgui-docking)
add_subdirectory(gueepo2D/engine)