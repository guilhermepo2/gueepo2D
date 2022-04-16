#include "gueepo2Dpch.h"
#include "SpriteComponent.h"
#include "core/renderer/BufferLayout.h"
#include "utils/Tilemap.h"

namespace gueepo {
	SpriteComponent::SpriteComponent(Texture* tex, int drawOrder /* = 1 */) : texture(tex), DrawOrder(drawOrder) {
		RebuildSourceRectangle();
	}

	SpriteComponent::SpriteComponent(Texture* tex, math::Vector2 min, math::Vector2 max, int drawOrder /* = 1 */) : texture(tex), DrawOrder(drawOrder) {
		RebuildSourceRectangle(min, max);
	}

	SpriteComponent::SpriteComponent(Texture* tex, int tile_x, int tile_y, int tile_width, int tile_height, int drawOrder /* = 1 */) : texture(tex), DrawOrder(drawOrder) {
		RebuildSourceRectangle(tile_x, tile_y, tile_width, tile_height);
	}

	SpriteComponent::SpriteComponent(Texture* tex, const Tile& tile, int drawOrder /*= 1*/) : texture(tex), DrawOrder(drawOrder) {
		RebuildFromTile(tile);
	}

	void SpriteComponent::RebuildSourceRectangle() {
		sourceRectangle.bottomLeft = math::Vector2::Zero;
		sourceRectangle.topRight = math::Vector2(static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()));
	}

	void SpriteComponent::RebuildSourceRectangle(math::Vector2 min, math::Vector2 max) {
		sourceRectangle.bottomLeft = min;
		sourceRectangle.topRight = max;
	}

	void SpriteComponent::RebuildSourceRectangle(int tile_x, int tile_y, int tile_width, int tile_height) {
		sourceRectangle.bottomLeft.x = static_cast<float>(tile_x * tile_width);
		sourceRectangle.bottomLeft.y = static_cast<float>(tile_y * tile_height);
		sourceRectangle.topRight.x = static_cast<float>((tile_x + 1) * tile_width);
		sourceRectangle.topRight.y = static_cast<float>((tile_y + 1) * tile_height);
	}

	void SpriteComponent::RebuildFromTile(const Tile& tile) {
		sourceRectangle = tile.GetRect();
	}

	void SpriteComponent::Render() {
		TransformComponent* t = Owner->GetComponentOfType<TransformComponent>();
		assert(t != nullptr, "trying to render something without a transform?!");

		math::Vector2 textureScaleVec(sourceRectangle.GetSize());
		
		if (FlipHorizontal) {
			textureScaleVec.x *= -1;
		}

		if (FlipVertical) {
			textureScaleVec.y *= -1;
		}

		math::Matrix4 textureScale = math::Matrix4::CreateScale(textureScaleVec);
		math::Matrix4 transformMatrix = textureScale * t->GetTransformMatrix();
		Renderer::Draw(transformMatrix, GetTexCoordsMin(), GetTexCoordsMax(), texture);
	}

	// ------------------------------------------------------------------------------------
	// Private Functions
	// ------------------------------------------------------------------------------------
	math::Vector2 SpriteComponent::GetTexCoordsMin() const {
		return math::Vector2(
			sourceRectangle.bottomLeft.x / texture->GetWidth(),
			sourceRectangle.bottomLeft.y / texture->GetHeight()
		);
	}

	math::Vector2 SpriteComponent::GetTexCoordsMax() const {
		return math::Vector2(
			sourceRectangle.topRight.x / texture->GetWidth(),
			sourceRectangle.topRight.y / texture->GetHeight()
		);
	}
}