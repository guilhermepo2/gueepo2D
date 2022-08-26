#pragma once
#include "core/math/Rect.h"
#include "core/renderer/Texture.h"
// A texture region is... a texture region
// A piece of a texture if you wanna think that way


namespace gueepo {

	class TextureRegion {
	public:
		TextureRegion(Texture* texture, int x, int y, int w, int h);

		inline Texture* GetTexture() const { return m_TextureRef; }
		inline math::rect GetCoordinates() const { return m_texCoords; }
	private:
		Texture* m_TextureRef;
		math::rect m_texCoords;
	};
}