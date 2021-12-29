cmake_minimum_required(VERSION 3.10)

project(dearimgui)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(dearimgui
    imconfig.h
    imgui_demo.cpp
    imgui_draw.cpp
	imgui_internal.h
	imgui_tables.cpp
	imgui_widgets.cpp
	imgui.cpp
	imgui.h
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
)