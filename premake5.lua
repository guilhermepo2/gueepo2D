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
        "%{IncludeDirectories.spdlog}"
    }

    libdirs
    {

    }

    links
    {

    }