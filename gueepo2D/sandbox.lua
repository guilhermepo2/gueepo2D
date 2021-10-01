project "Sandbox"
    location "sandbox"
    kind "ConsoleApp"
    language "C++"
    warnings "Extra"
    staticruntime "On"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/binobj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.location}/**.h",
        "%{prj.location}/**.cpp"
    }

    -- exactly the same as gueepo2D (this is not bueno?)
    includedirs
    {
        "engine",
        "%{IncludeDirectories.spdlog}",
        "%{IncludeDirectories.rapidjson}",
        "%{SDL2_INCLUDE_DIR}"
    }

    links
    {
        "gueepo2D"
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"