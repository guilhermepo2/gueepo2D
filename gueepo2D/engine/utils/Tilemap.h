#pragma once
#include "core/math/Rect.h"
#include <vector>

namespace gueepo {

	class Texture;

	class Tile {
	public:
		Tile(math::Rect tilePosition, int textureWidth, int textureHeight);
		~Tile();
		math::Rect GetRect() const { return m_TilePositionWorldCoords; }
		math::Rect GetTexCoords() const { return m_TilePositionTexCoords; }

	private:
		math::Rect m_TilePositionTexCoords;
		math::Rect m_TilePositionWorldCoords;
	};

	class Tilemap {
	public:
		Tilemap(Texture* tilemapTexture);
		~Tilemap();

		// #todo: read from json
		void Slice(int tileWidth, int tileHeight);

		const Tile& GetTile(int index) const;

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		uint16_t GetTileWidth()		const { return m_TileWidth;			}
		uint16_t GetTileHeight()	const { return m_TileHeight;		}
		uint16_t GetColumns()		const { return m_NumberOfColumns;	}
		uint16_t GetRows()			const { return m_NumberOfRows;		}
		size_t	GetNumberOfTiles()	const { return m_Tiles.size();		}

	private:
		Texture* m_tilemapTexture;
		std::vector<Tile> m_Tiles;

		uint16_t m_TileWidth;
		uint16_t m_TileHeight;
		uint16_t m_NumberOfColumns;
		uint16_t m_NumberOfRows;
	};
}