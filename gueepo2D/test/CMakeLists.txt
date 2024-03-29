project (gueepo2D-tests)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(${PROJECT_NAME}
    all_tests.cpp
    gueepo_vector.h
    TestUtils.h
    vector2.h
    vector3.h
    json.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2 gueepo2D-engine)

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}> )

target_link_directories(${PROJECT_NAME}
    PUBLIC
        ${SDL2_PATH}/lib/x64
)

if(EXISTS ${SDL2_PATH}/lib/x64/SDL2.dll)
    message("copying SDL2... " ${SDL2_PATH} "/lib/x64/SDL2/dll")
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_PATH}/lib/x64/SDL2.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>/../
    )
endif()


if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/../assets
    )
endif()

if(APPLE)
    add_compile_definitions(GUEEPO2D_MACOS)
endif()

message("adding tests")
add_test(NAME AllTests COMMAND ${PROJECT_NAME})