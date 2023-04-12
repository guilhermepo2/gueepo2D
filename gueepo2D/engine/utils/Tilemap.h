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
    public:
        Tilemap(const TILEMAP_PARAMS& params);
        void AddLayer(TilemapLayer* layer);
        inline int GetNumberOfLayers() const { return m_map.size(); }
        inline TilemapLayer* GetLayer(int idx) { return m_map[idx]; }

        inline int GetWidth() const { return m_width; }
        inline int GetHeight() const { return m_height; }
        inline int GetTileWidth() const { return m_tileWidth; }
        inline int GetTileHeight() const { return m_tileHeight; }

    private:
        gueepo::vector<TilemapLayer*> m_map;
        int m_width = 0, m_height = 0, m_tileWidth = 0, m_tileHeight = 0;
    };
}
