cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(gueepo2D-standalone)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(BUILD_TEST ON) # turn this on to build the test projects

add_subdirectory(gueepo2D/thirdparty/glad)
set_target_properties (glad PROPERTIES FOLDER thirdparty)

add_subdirectory(gueepo2D/engine)

if(BUILD_TEST)
    include(CTest)
    add_subdirectory(gueepo2D/test)
endif()
