#include "PixelPanel.h"
#include "core/renderer/Renderer.h"

namespace gueepo {
    
	PixelPanel::PixelPanel(const PIXEL_PANEL_PARAMS& params) {
		m_internalData = params;
	}

	void PixelPanel::Render() {
		if (!isVisible) {
			return;
		}

		int x = static_cast<int>(m_internalData.startPosition.x);
		int y;
		for (int i = 0; i < m_internalData.widthInTiles; i++) {

			y = static_cast<int>(m_internalData.startPosition.y);
			for (int j = 0; j < m_internalData.heightInTiles; j++) {
				gueepo::TextureRegion* panelTile = GetTextureToRender(i, j);
				gueepo::Renderer::Draw(panelTile, x, y, m_internalData.tileSize, m_internalData.tileSize);
				y -= m_internalData.tileSize;
			}
			x += m_internalData.tileSize;
			
		}
	}

	gueepo::TextureRegion* PixelPanel::GetTextureToRender(int x, int y) {
		if (x == 0 && y == 0) {
			return m_internalData.topLeft;
		}

		if (x == m_internalData.widthInTiles - 1 && y == m_internalData.heightInTiles - 1) {
			return m_internalData.bottomRight;
		}

		if (x == 0 && y == m_internalData.heightInTiles - 1) {
			return m_internalData.bottomLeft;
		}

		if (x == m_internalData.widthInTiles - 1 && y == 0) {
			return m_internalData.topRight;
		}

		if (x == 0) {
			return m_internalData.middleLeft;
		}

		if (x == m_internalData.widthInTiles - 1) {
			return m_internalData.middleRight;
		}

		if (y == 0) {
			return m_internalData.topMiddle;
		}

		if (y == m_internalData.heightInTiles - 1) {
			return m_internalData.bottomMiddle;
		}

		return m_internalData.middleMiddle;
	}

}