-- Dependencies
-- By design, SDL2 is not distributed with the engine.
-- https://www.libsdl.org/download-2.0.php
-- these are the paths that I am using
SDL2_INCLUDE_DIR = "gueepo2D/thirdparty/SDL2-2.0.16/include"
SDL2_LIB_DIR = "gueepo2D/thirdparty/SDL2-2.0.16/lib/x64"

workspace "gueepo2D"
    architecture "x64"

    configurations
    {
        "Debug"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}.%{cfg.architecture}"

IncludeDirectories = {}
IncludeDirectories["spdlog"] = "gueepo2D/thirdparty/spdlog-1.9.2/include"
LibDir = {}

project "gueepo2D"
    location "gueepo2D"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    warnings "Extra"

    targetdir("%{prj.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{prj.location}/binobj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.location}/engine/**.h",
        "%{prj.location}/engine/**.cpp",
    }

    includedirs
    {
        "%{prj.location}/engine",
        "%{IncludeDirectories.spdlog}",
        "%{SDL2_INCLUDE_DIR}"
    }

    libdirs
    {
        "%{SDL2_LIB_DIR}"
    }

    filter "system:windows"
        links
        {
            "SDL2.lib",
        }