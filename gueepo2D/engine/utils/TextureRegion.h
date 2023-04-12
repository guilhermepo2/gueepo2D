//
// TextureRegion.h
// @description a texture region describes a piece of a texture in texture coordinates (in between 0 and 1)
//

#pragma once
#include "core/math/rect.h"
#include "core/renderer/Texture.h"
// A texture region is... a texture region
// A piece of a texture if you wanna think that way


namespace gueepo {

	class TextureRegion {
	public:
		TextureRegion(Texture* texture, int x, int y, int w, int h);

		inline Texture* GetTexture() const { return m_TextureRef; }
		inline math::rect GetCoordinates() const { return m_texCoords; }
        inline int GetWidth() const { return m_width; }
        inline int GetHeight() const { return m_height; }
	private:
		Texture* m_TextureRef;
		math::rect m_texCoords;
        int m_width;
        int m_height;
	};
}