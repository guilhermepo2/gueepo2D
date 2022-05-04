#include "gueepo2Dpch.h"

#include "Tilemap.h"
#include "core/Log.h"
#include "core/renderer/Texture.h"

namespace gueepo {

	Tile::Tile(math::Rect tilePosition, int textureWidth, int textureHeight) : m_TilePositionTexCoords(tilePosition) {
		m_TilePositionWorldCoords =
			math::Rect(
				math::Vector2(tilePosition.bottomLeft.x * textureWidth, tilePosition.bottomLeft.y * textureHeight),
				math::Vector2(tilePosition.topRight.x * textureWidth, tilePosition.topRight.y * textureHeight)
			);
	}

	Tile::~Tile() { /* nothing to do here */ }

	Tilemap::Tilemap(Texture* tilemapTexture) : m_tilemapTexture(tilemapTexture), m_TileWidth(0), m_TileHeight(0), m_NumberOfColumns(0), m_NumberOfRows(0) {
		m_Tiles.clear();
	}

	Tilemap::~Tilemap() {}

	void Tilemap::Slice(int tileWidth, int tileHeight) {
		m_Tiles.clear();
		m_TileWidth = tileWidth;
		m_TileHeight = tileHeight;

		assert(m_tilemapTexture != nullptr, "Can't slice a Tilemap with a null texture!");

		m_NumberOfRows = (m_tilemapTexture->GetHeight() / m_TileHeight);
		m_NumberOfColumns = (m_tilemapTexture->GetWidth() / m_TileWidth);

		float th = static_cast<float>(m_TileHeight) / m_tilemapTexture->GetHeight();
		float tw = static_cast<float>(m_TileWidth) / m_tilemapTexture->GetWidth();
		for (int i = 0; i < m_NumberOfRows; i++) {
			for (int j = 0; j < m_NumberOfColumns; j++) {
				int x = i;
				int y = j;
				math::Vector2 min = math::Vector2(x * tw, y * th);
				math::Vector2 max = math::Vector2( (x + 1) * tw, (y + 1) * th);

				m_Tiles.push_back(Tile(math::Rect(min, max), m_tilemapTexture->GetWidth(), m_tilemapTexture->GetHeight()));
			}
		}
	}

	const gueepo::Tile& Tilemap::GetTile(int index) const {
		assert(0 <= index && m_Tiles.size() >= index, "index is not within range of tilemap!");

		return m_Tiles[index];

	}

	uint32_t Tilemap::GetWidth() const { assert(m_tilemapTexture != nullptr, "tilemap texture is null!"); return m_tilemapTexture->GetHeight(); }
	uint32_t Tilemap::GetHeight() const	{ assert(m_tilemapTexture != nullptr, "tilemap texture is null!"); return m_tilemapTexture->GetWidth(); }

	Tilemap* Tilemap::Create(Texture* tilemapTexture) {
		return new Tilemap(tilemapTexture);
	}

}
