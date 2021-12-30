project(gueepo2D-sandbox)

add_executable(gueepo2D-sandbox
    Broughlike.h
    Broughlike.cpp
    TileComponent.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_directories(${PROJECT_NAME}
    PUBLIC
        ${SDL2_PATH}/lib/x64
)

target_link_libraries(${PROJECT_NAME} gueepo2D-engine)

if(EXISTS ${SDL2_PATH}/lib/x64/SDL2.dll)
    message("copying SDL2... " ${SDL2_PATH} "/lib/x64/SDL2/dll")
    add_custom_command(
        TARGET gueepo2D-sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_PATH}/lib/x64/SDL2.dll $<TARGET_FILE_DIR:gueepo2D-sandbox>/../
    )
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    add_custom_command(
        TARGET gueepo2D-sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:gueepo2D-sandbox>/../assets
    )
endif()