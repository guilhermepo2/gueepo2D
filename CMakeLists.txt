cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(gueepo2D)

# ${CMAKE_SOURCE_DIR}
# ${CMAKE_CURRENT_BINARY_DIR}

# this should be in a dependencies subproject
add_subdirectory(gueepo2D/thirdparty/glad)
add_subdirectory(gueepo2D/thirdparty/imgui-docking)
add_subdirectory(gueepo2D/engine)
add_subdirectory(gueepo2D/sandbox)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT gueepo2D-sandbox)
