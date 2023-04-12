//
// ImageUtils.h
// Helper functions to deal images, it uses stb libraries to do that
//

#pragma once

namespace gueepo {
	unsigned char* g_LoadImage(const char* path, int& outImageWidth, int& outImageHeight, int& outComponentsPerPixel, int stride = 0, bool flip = true);
	bool g_FreeImage(void* data);
	bool g_SaveImage(const char* path, int width, int height, int comp, const void* data, int stride = 0);
}