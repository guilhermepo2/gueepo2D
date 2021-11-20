#pragma once

namespace gueepo {
	static unsigned char* LoadImage(const char* path, int& outImageWidth, int& outImageHeight, int& outComponentsPerPixel, int stride = 0);
	static bool FreeImage(void* data);
	static bool SaveImage(const char* path, int width, int height, int comp, const void* data, int stride = 0);
}