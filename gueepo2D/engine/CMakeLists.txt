project(gueepo2D-engine VERSION 0.1 DESCRIPTION "gueepo2D game engine v0.1")
include(FindSDL2.cmake)

set(PLATFORM_SDL2 true CACHE BOOL "Use SDL2 Platform Backend")
set(GRAPHICS_OPENGL true CACHE BOOL "Use OpenGL Graphics Backend")
# optional: SDL2_PATH can be defined here, it has to be an absolute path to SDL2 root folder (i.e. D:/workspace/SDL2-2.0.18)

set (SOURCES
    "gueepo2Dpch.cpp"

    "core/Application.cpp"
    "core/ImGuiLayer.cpp"
    "core/Log.cpp"

    "core/audio/Audio.cpp"

    "core/Containers/hashed_string.cpp"
    "core/Containers/string.cpp"

    "core/filesystem/File.cpp"
    "core/filesystem/Filesystem.cpp"
    "core/filesystem/Font.cpp"
    "core/filesystem/json.cpp"

    "core/input/Input.cpp"
    "core/layer/Layer.cpp"
    "core/layer/LayerStack.cpp"

    "core/math/mat4.cpp"
    "core/math/rand.cpp"
    "core/math/vec2.cpp"
    "core/math/vec3.cpp"

    "core/renderer/GraphicsContext.cpp"
    "core/renderer/IndexBuffer.cpp"
    "core/renderer/IndexBuffer.cpp"
    "core/renderer/OrtographicCamera.cpp"
    "core/renderer/Renderer.cpp"
    "core/renderer/RendererAPI.cpp"
    "core/renderer/Shader.cpp"
    "core/renderer/SpriteBatcher.cpp"
    "core/renderer/Texture.cpp"
    "core/renderer/VertexArray.cpp"
    "core/renderer/VertexBuffer.cpp"
    "core/renderer/FontSprite.cpp"

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
    "utils/TextureRegion.cpp"
    "utils/PixelBuffer.cpp"
    "utils/SpriteAnimation.cpp"
)

set(HEADERS
    "gueepo2d.h"
    "gueepo2Dpch.h"

    "core/macos_common.h"

    "core/Application.h"
    "core/Common.h"
    "core/EntryPoint.h"
    "core/ImGuiLayer.h"
    "core/Log.h"
    "core/TimeStep.h"
    "core/Window.h"

    "core/audio/Audio.h"

    "core/Containers/hashed_string.h"
    "core/Containers/string.h"
    "core/Containers/vector.h"

    "core/Debug/Profiler.h"

    "core/events/ApplicationEvent.h"
    "core/events/Event.h"
    "core/events/EventDispatcher.h"
    "core/events/KeyEvent.h"
    "core/events/MouseEvent.h"

    "core/filesystem/File.h"
    "core/filesystem/Filesystem.h"
    "core/filesystem/Font.h"
    "core/filesystem/json.h"
    
    "core/input/Input.h"
    "core/input/KeyboardCodes.h"
    "core/input/MouseCodes.h"
    "core/layer/Layer.h"
    "core/layer/LayerStack.h"

    "core/math/math.h"
    "core/math/endian.h"
    "core/math/rect.h"
    "core/math/mat4.h"
    "core/math/rand.h"
    "core/math/vec2.h"
    "core/math/vec3.h"

    "core/renderer/BufferLayout.h"
    "core/renderer/Color.h"
    "core/renderer/GraphicsContext.h"
    "core/renderer/IndexBuffer.h"
    "core/renderer/OrtographicCamera.h"
    "core/renderer/Renderer.h"
    "core/renderer/RendererAPI.h"
    "core/renderer/Shader.h"
    "core/renderer/SpriteBatcher.h"
    "core/renderer/Texture.h"
    "core/renderer/VertexArray.h"
    "core/renderer/VertexBuffer.h"
    "core/renderer/FontSprite.h"

    "platform/OpenGL/imgui_impl_opengl3_loader.h"
    "platform/OpenGL/imgui_impl_opengl3.h"
    "platform/OpenGL/OpenGLContext.h"
    "platform/OpenGL/OpenGLIndexBuffer.h"
    "platform/OpenGL/OpenGLRendererAPI.h"
    "platform/OpenGL/OpenGLShader.h"
    "platform/OpenGL/OpenGLTexture.h"
    "platform/OpenGL/OpenGLVertexArray.h"
    "platform/OpenGL/OpenGLVertexBuffer.h"
    "platform/SDL2/imgui_impl_sdl.h"
    "platform/SDL2/SDL2Input.h"
    "platform/SDL2/SDL2Window.h"

    "utils/ImageUtils.h"
    "utils/TextureRegion.h"
    "utils/PixelBuffer.h"
    "utils/SpriteAnimation.h"
)

message(${CMAKE_CURRENT_SOURCE_DIR})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" PREFIX "Source Files" FILES ${SOURCES})

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories (${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/spdlog-1.9.2/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/glad/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/imgui-docking>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/rapidjson-1.1.0/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/stb>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../thirdparty/miniaudio>
)

target_link_libraries(${PROJECT_NAME} glad dearimgui)

if(WIN32)
    add_compile_definitions(GUEEPO2D_WINDOWS)
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
endif()

if(APPLE)
    message("defining for apple")
    add_compile_definitions(GUEEPO2D_MACOS)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
    message("- source dir: ${PROJECT_SOURCE_DIR}")
    message("- sdl2 library: ${SDL2_LIBRARY}")
    message("- sdl2 dir: ${SDL2_INCLUDE_DIR}")
endif()

if(GRAPHICS_OPENGL)
    if(WIN32)
        target_link_libraries(${PROJECT_NAME} opengl32.lib)
    endif()

    if(APPLE)
        # target_link_libraries(${PROJECT_NAME} OpenGL)
    endif()

    add_compile_definitions(GUEEPO2D_GRAPHICS_OPENGL)
endif()

target_precompile_headers(${PROJECT_NAME}
    PUBLIC gueepo2Dpch.h
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DGUEEPO2D_DEBUG")

if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lGL -lSDL2 -framework OpenGL")
endif()