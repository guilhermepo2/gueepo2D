#pragma once
#include "Component.h"
#include "core/Log.h"
#include "core/renderer/Texture.h"
#include "core/math/Math.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "core/renderer/Shader.h"
#include "core/renderer/VertexArray.h"
#include "core/renderer/Renderer.h"

namespace gueepo {

	class Tile;

	class SpriteComponent : public Component {	
	public:
		Texture* texture;
		int DrawOrder = 1;
		// todo: color (should be in the material?)
		bool FlipHorizontal = false;
		bool FlipVertical = false;
		math::rect sourceRectangle;

		SpriteComponent() : texture(nullptr) {}

		/* Assumes that sourceRectangle is (0,0) (textureWidth, textureHeight)*/
		SpriteComponent(Texture* tex, int drawOrder = 1);

		/* Explicitly passes sourceRectangle min and max points */
		SpriteComponent(Texture* tex, math::vec2 min, math::vec2 max, int drawOrder = 1);

		/* 
			Calculates the source rectangle given the tile position and tile size
			Not the best function signature, but hopefully this won't be used a lot :)
		*/
		SpriteComponent(Texture* tex, int tile_x, int tile_y, int tile_width, int tile_height, int drawOrder = 1);

		/* Gets the source rectangle from the tile */
		SpriteComponent(Texture* tex, const Tile& tile, int drawOrder = 1);

		void RebuildSourceRectangle();
		void RebuildSourceRectangle(math::vec2 min, math::vec2 max);
		void RebuildSourceRectangle(int tile_x, int tile_y, int tile_width, int tile_height);
		void RebuildFromTile(const Tile& tile);

		void Render() override;

	private:
		math::vec2 GetTexCoordsMin() const;
		math::vec2 GetTexCoordsMax() const;
	};
}