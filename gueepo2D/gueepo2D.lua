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

        -- imgui (todo: make its own project?)
        -- "thirdparty/imgui-docking/*.h",
        -- "thirdparty/imgui-docking/*.cpp"
    }

    includedirs
    {
        "engine",
        "%{IncludeDirectories.spdlog}",
        "%{IncludeDirectories.rapidjson}",
        "%{IncludeDirectories.glad}",
        -- "%{IncludeDirectories.dearimgui}",
        "%{SDL2_INCLUDE_DIR}"
    }

    libdirs
    {
        "%{SDL2_LIB_DIR}"
    }

    links
    {
        "glad"
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        links
        {
            "SDL2.lib",
            "opengl32.lib"
        }

        defines
        {
            "GUEEPO_PLATFORM_WINDOWS"
        }
    
    filter "system:linux"
        defines
        {
            "GUEEPO_PLATFORM_LINUX"
        }
    
    filter "system:macosx"
        defines
        {
            "GUEEPO_PLATFORM_MACOS"
        }