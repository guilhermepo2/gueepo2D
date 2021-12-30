project(gueepo2D-engine VERSION 0.1 DESCRIPTION "gueepo2D game engine v0.1 (alpha?)")

set(PLATFORM_SDL2 true CACHE BOOL "Use SDL2 Platform Backend")
set(GRAPHICS_OPENGL true CACHE BOOL "Use OpenGL Graphics Backend")

add_library(${PROJECT_NAME} STATIC
    gueepo2Dpch.cpp

    core/Application.cpp
    core/ImGuiLayer.cpp
    core/Log.cpp
    core/filesystem/File.cpp
    core/GameObject/Entity.cpp
    core/GameObject/GameObject.cpp
    core/GameObject/SpriteComponent.cpp
    core/input/Input.cpp
    core/layer/Layer.cpp
    core/layer/LayerStack.cpp
    core/math/Matrix4.cpp
    core/math/Random.cpp
    core/math/Vector2.cpp
    core/math/Vector3.cpp
    core/renderer/GraphicsContext.cpp
    core/renderer/IndexBuffer.cpp
    core/renderer/IndexBuffer.cpp
    core/renderer/OrtographicCamera.cpp
    core/renderer/RenderCommand.cpp
    core/renderer/Renderer.cpp
    core/renderer/RendererAPI.cpp
    core/renderer/Shader.cpp
    core/renderer/Texture.cpp
    core/renderer/VertexArray.cpp
    core/renderer/VertexBuffer.cpp
    
    platform/SDL2/imgui_impl_sdl.cpp
    platform/SDL2/SDL2Input.cpp
    platform/SDL2/SDL2TimeStep.cpp
    platform/SDL2/SDL2Window.cpp

    platform/OpenGL/imgui_impl_opengl3.cpp
    platform/OpenGL/OpenGLContext.cpp
    platform/OpenGL/OpenGLIndexBuffer.cpp
    platform/OpenGL/OpenGLRendererAPI.cpp
    platform/OpenGL/OpenGLShader.cpp
    platform/OpenGL/OpenGLTexture.cpp
    platform/OpenGL/OpenGLVertexArray.cpp
    platform/OpenGL/OpenGLVertexBuffer.cpp

    utils/ImageUtils.cpp
    utils/JsonHelper.cpp
)

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
    target_link_libraries(${PROJECT_NAME} SDL2.lib)
    target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/../thirdparty/SDL2-2.0.18/include
    )
endif()

if(GRAPHICS_OPENGL)
    target_link_libraries(${PROJECT_NAME} opengl32.lib)
endif()

target_precompile_headers(${PROJECT_NAME}
    PUBLIC gueepo2Dpch.h
)