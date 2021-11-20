#pragma once

namespace gueepo {
	unsigned char* g_LoadImage(const char* path, int& outImageWidth, int& outImageHeight, int& outComponentsPerPixel, int stride = 0);
	bool g_FreeImage(void* data);
	bool g_SaveImage(const char* path, int width, int height, int comp, const void* data, int stride = 0);
}