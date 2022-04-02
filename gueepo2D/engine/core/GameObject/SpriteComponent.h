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

/*
* The signature for the Submit function (submitting stuff to render) is:
*	Submit(VertexArray*, Shader*)
* now, since this is a 2D game engine, we can assume default VAs and default Shaders, but
* we have to keep in mind  away to be able to customize or change this, or whatever
* Ideally a sprite component would have a "Material" which would have its own shader, and mayhaps its own VA (because we need to inform the vertex buffer layout
*/

namespace gueepo {
	class SpriteComponent : public Component {	
	public:
		Texture* texture;
		int DrawOrder = 1;
		// todo: color (should be in the material?)
		bool FlipHorizontal = false;
		bool FlipVertical = false;
		math::Rect sourceRectangle;

		SpriteComponent() : texture(nullptr) {}

		/* Assumes that sourceRectangle is (0,0) (textureWidth, textureHeight)*/
		SpriteComponent(Texture* tex, int drawOrder = 1);

		/* Explicitly passes sourceRectangle min and max points */
		SpriteComponent(Texture* tex, math::Vector2 min, math::Vector2 max, int drawOrder = 1);

		/* 
			Calculates the source rectangle given the tile position and tile size
			Not the best function signature, but hopefully this won't be used a lot :)
		*/
		SpriteComponent(Texture* tex, int tile_x, int tile_y, int tile_width, int tile_height, int drawOrder = 1);

		void RebuildSourceRectangle();
		void RebuildSourceRectangle(math::Vector2 min, math::Vector2 max);
		void RebuildSourceRectangle(int tile_x, int tile_y, int tile_width, int tile_height);

		void Render() override;

	private:
		math::Vector2 GetTexCoordsMin() const;
		math::Vector2 GetTexCoordsMax() const;
	};
}