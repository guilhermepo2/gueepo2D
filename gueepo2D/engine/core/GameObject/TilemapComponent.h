#pragma once
#include "Component.h"
#include <vector>
#include "Entity.h"
#include "TransformComponent.h"
#include "core/filesystem/json.h"
#include "core/renderer/Texture.h"
#include "utils/Tilemap.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/SpriteBatcher.h"

namespace gueepo {
	class TilemapComponent : public Component {
	public:
		std::vector<int> data;
		int width;
		int height;
		Tilemap* tm;

		TilemapComponent() : width(0), height(0), tm(nullptr) {}
		
		void LoadFromTiled(Tilemap* t, gueepo::json& file) {
			tm = t;

			std::vector<gueepo::json> layers;
			file.GetArray("layers", layers);

			layers[0].GetIntArray("data", data);
			layers[0].GetInt("width", width);
			layers[0].GetInt("height", height);
		}

		void Render() override {
			TransformComponent* t = Owner->GetComponentOfType<TransformComponent>();
			g2dassert(t != nullptr, "trying to render something without a transform?!");

			int v = 0;
			math::vec2 pos = t->position;
			math::vec2 scale = t->scale;
			float initialX = pos.x;

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {

					int value = data[v] - 1;
					Tile currentTile = tm->GetTile(value);
					
					
					math::mat4 tileScale = math::mat4::CreateScale(currentTile.GetRect().GetSize());
					math::mat4 transformMatrix = math::mat4::CreateScale(scale) * math::mat4::CreateRotation(0.0f) * math::mat4::CreateTranslation(pos);
					Renderer::s_spriteBatcher->Draw(tileScale * transformMatrix, currentTile.GetTexCoords().bottomLeft, currentTile.GetTexCoords().topRight, tm->GetTexture());

					pos.x += width * scale.x;
					v++;
				}
				pos.y -= height * scale.y;
				pos.x = initialX;
			}
		}
	};
}