#pragma once

#if GUEEPO2D_PLATFORM_WINDOWS || _WINDOWS
#include <Windows.h>
#elif GUEEPO2D_PLATFORM_LINUX
// not implemented
#elif GUEEPO2D_PLATFORM_MACOS
// not implemented
#else
// no platform defined?
#endif

#if GUEEPO2D_PLATFORM_SDL2
// defined sdl2 :3
#else
// no platform defined?
#endif

#if GUEEPO2D_GRAPHICS_OPENGL
// define something here?
#elif GUEEPO2D_GRAPHICS_DIRECTX
// not implemented
#elif GUEEPO2D_GRAPHICS_VULKAN
// not implemented
#elif GUEEPO2D_GRAPHICS_METAL
// not implemented
#else
// no graphics defined?
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <memory>

// ================================
// gueepo2D includes
// ================================
#include "core/Log.h"