project "gueepo2D"
    kind "StaticLib"
    language "C++"
    staticruntime "On"
    warnings "Extra"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/binobj/" .. outputdir .. "/%{prj.name}")

    pchheader "gueepo2Dpch.h"
    pchsource "engine/gueepo2Dpch.cpp"

    files
    {
        "engine/**.h",
        "engine/**.cpp",
    }

    includedirs
    {
        "engine",
        "%{IncludeDirectories.spdlog}",
        "%{IncludeDirectories.rapidjson}",
        "%{SDL2_INCLUDE_DIR}"
    }

    libdirs
    {
        "%{SDL2_LIB_DIR}"
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        links
        {
            "SDL2.lib",
        }

        defines
        {
            "GUEEPO_PLATFORM_WINDOWS"
        }