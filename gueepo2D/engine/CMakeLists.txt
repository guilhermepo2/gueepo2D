project(gueepo2D-engine VERSION 0.1 DESCRIPTION "gueepo2D game engine v0.1")

set(PLATFORM_SDL2 true CACHE BOOL "Use SDL2 Platform Backend")
set(GRAPHICS_OPENGL true CACHE BOOL "Use OpenGL Graphics Backend")
# optional: SDL2_PATH can be defined here, it has to be an absolute path to SDL2 root folder (i.e. D:/workspace/SDL2-2.0.18)

set (SOURCES
    "gueepo2Dpch.cpp"

    "core/Application.cpp"
    "core/ImGuiLayer.cpp"
    "core/Log.cpp"
    "core/Containers/String.cpp"
    "core/input/Input.cpp"
    "core/layer/Layer.cpp"
    "core/layer/LayerStack.cpp"
    "core/math/Matrix4.cpp"
    "core/math/Random.cpp"
    "core/math/Vector2.cpp"
    "core/math/Vector3.cpp"
    "core/renderer/GraphicsContext.cpp"
    "core/renderer/IndexBuffer.cpp"
    "core/renderer/IndexBuffer.cpp"
    "core/renderer/OrtographicCamera.cpp"
    "core/renderer/Renderer.cpp"
    "core/renderer/RendererAPI.cpp"
    "core/renderer/Shader.cpp"
    "core/renderer/Texture.cpp"
    "core/renderer/VertexArray.cpp"
    "core/renderer/VertexBuffer.cpp"

    "core/filesystem/File.cpp"
    "core/GameObject/Entity.cpp"
    "core/GameObject/GameObject.h"
    "core/GameObject/GameObject.cpp"
    "core/GameObject/SpriteComponent.h"
    "core/GameObject/SpriteComponent.cpp"

    "platform/SDL2/imgui_impl_sdl.cpp"
    "platform/SDL2/SDL2Input.cpp"
    "platform/SDL2/SDL2TimeStep.cpp"
    "platform/SDL2/SDL2Window.cpp"
    "platform/OpenGL/imgui_impl_opengl3.cpp"
    "platform/OpenGL/OpenGLContext.cpp"
    "platform/OpenGL/OpenGLIndexBuffer.cpp"
    "platform/OpenGL/OpenGLRendererAPI.cpp"
    "platform/OpenGL/OpenGLShader.cpp"
    "platform/OpenGL/OpenGLTexture.cpp"
    "platform/OpenGL/OpenGLVertexArray.cpp"
    "platform/OpenGL/OpenGLVertexBuffer.cpp"

    "utils/ImageUtils.cpp"
    "utils/JsonHelper.cpp"
)

set(HEADERS
    "core/Containers/String.h"
    "core/GameObject/Entity.h"
    "core/GameObject/Component.h"
    "core/GameObject/TransformComponent.h"
)

source_group( ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
source_group( ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/spdlog-1.9.2/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/glad/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/imgui-docking>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/rapidjson-1.1.0/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/stb>
)

target_link_libraries(${PROJECT_NAME} glad dearimgui)

if(PLATFORM_SDL2)

    if(EXISTS SDL2_PATH)
        message("found SDL2_PATH")
        set(SDL2_FOUND true)
    else()
        set(SDL2_FOUND false)
    endif()

    if(NOT ${SDL2_FOUND})
        message("downloading SDL2...")
        
        include(FetchContent)
        FetchContent_Declare(
            SDL2
            URL     https://www.libsdl.org/release/SDL2-devel-2.0.18-VC.zip
            URL_MD5 701b791e8d3f39d018acb2be4be4b0b5
        )
        FetchContent_MakeAvailable(SDL2)
        message("SDL2 SOURCE DIR: " ${sdl2_SOURCE_DIR})
        set(SDL2_PATH ${sdl2_SOURCE_DIR} CACHE INTERNAL "sdl2 root path")
    endif()

    target_link_libraries(${PROJECT_NAME} SDL2.lib)
    target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_PATH}/include)
    add_compile_definitions(GUEEPO2D_PLATFORM_SDL2)
endif()

if(GRAPHICS_OPENGL)
    target_link_libraries(${PROJECT_NAME} opengl32.lib)
    add_compile_definitions(GUEEPO2D_GRAPHICS_OPENGL)
endif()

target_precompile_headers(${PROJECT_NAME}
    PUBLIC gueepo2Dpch.h
)