cmake_minimum_required(VERSION 3.10)
project(gueepo2D-sandbox)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

link_directories(../thirdparty/SDL2-2.0.18/lib/x64)

include_directories(
    ../engine
    ../thirdparty/spdlog-1.9.2/include
    ../thirdparty/glad/include
    ../thirdparty/imgui-docking
    ../thirdparty/rapidjson-1.1.0/include
    ../thirdparty/stb
)

add_executable(gueepo2D-sandbox
    Broughlike.h
    Broughlike.cpp
    TileComponent.h
)

target_link_libraries(gueepo2D-sandbox gueepo2D-engine)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/SDL2-2.0.18/lib/x64/SDL2.dll)
    add_custom_command(
        TARGET gueepo2D-sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/SDL2-2.0.18/lib/x64/SDL2.dll $<TARGET_FILE_DIR:gueepo2D-sandbox>/../
    )
else()
    message(WARNING "could not find SDL2.dll!")
    message(WARNING ${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    add_custom_command(
        TARGET gueepo2D-sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:gueepo2D-sandbox>/../assets
    )
endif()