#pragma once

//
// PixelPanel.h
// @description The Pixel panel is a panel that is defined in tiles. It needs 9 texture regions, a tile size, and a size in amount of tiles

#include "Control.h"
#include "utils/TextureRegion.h"

namespace gueepo {
    struct PIXEL_PANEL_PARAMS {
        int tileSize;
        int widthInTiles;
        int heightInTiles;
        gueepo::math::vec2 startPosition;

        TextureRegion* topLeft;
        TextureRegion* middleLeft;
        TextureRegion* bottomLeft;

		TextureRegion* topMiddle;
		TextureRegion* middleMiddle;
		TextureRegion* bottomMiddle;

		TextureRegion* topRight;
		TextureRegion* middleRight;
		TextureRegion* bottomRight;
        
    };

    class PixelPanel : public Control {
    public:
        PixelPanel(const PIXEL_PANEL_PARAMS& params);
        void Render() override;

    protected:
        PIXEL_PANEL_PARAMS m_internalData;

    private:
        TextureRegion* GetTextureToRender(int x, int y);
    };
}