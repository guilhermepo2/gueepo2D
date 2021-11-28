#include "gueepo2Dpch.h"
#include "ImageUtils.h"
#include "core/Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace gueepo {

	unsigned char* g_LoadImage(const char* path, int& outImageWidth, int& outImageHeight, int& outComponentsPerPixel, int stride, bool flip) {
		stbi_set_flip_vertically_on_load(flip ? 1 : 0);
		unsigned char* data = stbi_load(path, &outImageWidth, &outImageHeight, &outComponentsPerPixel, stride);

		if (data == nullptr) {
			LOG_ERROR("couldn't load image: {0}", path);
		}

		LOG_INFO("image {0} was loaded", path);
		return data;
	}

	bool g_FreeImage(void* data) {
		if (data == nullptr) {
			return false;
		}

		stbi_image_free(data);
		return true;
	}

	bool g_SaveImage(const char* path, int width, int height, int comp, const void* data, int stride) {
		int savingStatus = stbi_write_png(path, width, height, comp, data, stride);
		
		if (savingStatus == 0) {
			LOG_ERROR("failed to save image at {0}", path);
			return false;
		}

		LOG_INFO("image {0} saved successfuly", path);
		return true;
	}

}