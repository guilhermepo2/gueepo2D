#pragma once
#include "core/math/Rect.h"
#include <vector>

namespace gueepo {

	class Texture;

	class Tile {
	public:
		Tile(math::Rect tilePosition);
		~Tile();

	private:
		math::Rect m_TilePosition;
	};

	class Tilemap {
	public:
		Tilemap(Texture* tilemapTexture);
		~Tilemap();

		// #todo: read from json
		void Slice(int tileWidth, int tileHeight);

		uint32_t GetWidth();
		uint32_t GetHeight();

	private:
		Texture* m_tilemapTexture;
		std::vector<Tile> m_Tiles;
	};
}