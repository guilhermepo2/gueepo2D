workspace "gueepo2D"
    architecture "x64"

    configurations
    {
        "Debug"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}.%{cfg.architecture}"

IncludeDirectories = {}
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
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp",
    }

    includedirs
    {

    }

    libdirs
    {

    }

    links
    {

    }