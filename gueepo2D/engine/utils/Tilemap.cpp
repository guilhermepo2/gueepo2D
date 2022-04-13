#include "gueepo2Dpch.h"

#include "Tilemap.h"
#include "core/Log.h"
#include "core/renderer/Texture.h"

namespace gueepo {

	Tile::Tile(math::Rect tilePosition) : m_TilePosition(tilePosition) {}
	Tile::~Tile() { /* nothing to do here */ }

	Tilemap::Tilemap(Texture* tilemapTexture) : m_tilemapTexture(tilemapTexture) {
		m_Tiles.clear();
	}

	Tilemap::~Tilemap() {}

	void Tilemap::Slice(int tileWidth, int tileHeight) {
		// if there was something here, there isn't anymore lol
		m_Tiles.clear();

		assert(m_tilemapTexture != nullptr, "Can't slice a Tilemap with a null texture!");

		// #todo: make it work
	}

	uint32_t Tilemap::GetWidth() { assert(m_tilemapTexture != nullptr, "tilemap texture is null!"); return m_tilemapTexture->GetHeight(); }
	uint32_t Tilemap::GetHeight()	{ assert(m_tilemapTexture != nullptr, "tilemap texture is null!"); return m_tilemapTexture->GetWidth(); }

}
