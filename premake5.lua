-- Dependencies
-- By design, SDL2 is not distributed with the engine.
-- https://www.libsdl.org/download-2.0.php
-- these are the paths that I am using
SDL2_INCLUDE_DIR = "%{wks.location}/thirdparty/SDL2-2.0.16/include"
SDL2_LIB_DIR = "%{wks.location}/thirdparty/SDL2-2.0.16/lib/x64"

workspace "gueepo2D"
    location "gueepo2D"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}.%{cfg.architecture}"

IncludeDirectories = {}
IncludeDirectories["spdlog"] = "%{wks.location}/thirdparty/spdlog-1.9.2/include"
IncludeDirectories["rapidjson"] = "%{wks.location}/thirdparty/rapidjson-1.1.0/include"
IncludeDirectories["glad"] = "%{wks.location}/thirdparty/glad/include"
IncludeDirectories["dearimgui"] = "%{wks.location}/thirdparty/imgui-docking"
LibDir = {}

group "Dependencies"
    include "gueepo2D/thirdparty/glad"
    include "gueepo2D/thirdparty/imgui-docking"

group "gueepo2D"
    include "gueepo2D/gueepo2D.lua"
    include "gueepo2D/sandbox.lua"
