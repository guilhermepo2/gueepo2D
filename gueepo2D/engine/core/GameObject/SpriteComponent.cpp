#include "gueepo2Dpch.h"
#include "SpriteComponent.h"
#include "core/renderer/BufferLayout.h"

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

	void SpriteComponent::RebuildSourceRectangle() {
		sourceRectangle.min = math::Vector2::Zero;
		sourceRectangle.max = math::Vector2(texture->GetWidth(), texture->GetHeight());
	}

	void SpriteComponent::RebuildSourceRectangle(math::Vector2 min, math::Vector2 max) {
		sourceRectangle.min = min;
		sourceRectangle.max = max;
	}

	void SpriteComponent::RebuildSourceRectangle(int tile_x, int tile_y, int tile_width, int tile_height) {
		sourceRectangle.min.x = tile_x * tile_width;
		sourceRectangle.min.y = tile_y * tile_height;
		sourceRectangle.max.x = (tile_x + 1) * tile_width;
		sourceRectangle.max.y = (tile_y + 1) * tile_height;
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
			sourceRectangle.min.x / texture->GetWidth(),
			sourceRectangle.min.y / texture->GetHeight()
		);
	}

	math::Vector2 SpriteComponent::GetTexCoordsMax() const {
		return math::Vector2(
			sourceRectangle.max.x / texture->GetWidth(),
			sourceRectangle.max.y / texture->GetHeight()
		);
	}
}