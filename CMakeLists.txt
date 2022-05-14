cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(gueepo2D)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(BUILD_TEST OFF) # turn this on to build the test projects

add_subdirectory(gueepo2D/thirdparty/glad)
add_subdirectory(gueepo2D/thirdparty/imgui-docking)
set_target_properties (glad dearimgui PROPERTIES FOLDER thirdparty)

add_subdirectory(gueepo2D/engine)
add_subdirectory(gueepo2D/sandbox)

if(BUILD_TEST)
    add_subdirectory(gueepo2D/test)
endif()


if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT gueepo2D-sandbox)
endif()
