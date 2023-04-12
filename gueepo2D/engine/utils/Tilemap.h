//
// Tilemap.h
// @description The tilemap class is a representation of a map composed by tiles. A tile is a structure with a position (x,y) and a Texture.
//

#pragma once
#include "gueepo2d.h"

namespace gueepo {
    struct TILEMAP_PARAMS {
        int width, height;
        int tileWidth, tileHeight;
    };

    struct Tile {
        int x, y;
        TextureRegion* texture;
    };

    struct TilemapLayer {
        gueepo::vector<Tile*> data;
        gueepo::string layerName;
    };

    class Tilemap {
        Tilemap(const TILEMAP_PARAMS& params);
        void AddLayer(TilemapLayer* layer);

    private:
        gueepo::vector<TilemapLayer*> m_map;
        int m_width = 0, m_height = 0, m_tileWidth = 0, m_tileHeight = 0;
    };
}
