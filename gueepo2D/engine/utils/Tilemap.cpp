#include "Tilemap.h"

namespace gueepo {
	Tilemap::Tilemap(const TILEMAP_PARAMS& params) : m_width(params.width), m_height(params.height), m_tileWidth(params.tileWidth), m_tileHeight(params.tileHeight) {}
	void Tilemap::AddLayer(TilemapLayer* layer) { m_map.add(layer); }
}
