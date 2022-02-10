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

		SpriteComponent() : texture(nullptr) {}
		SpriteComponent(Texture* tex, int drawOrder = 1) : texture(tex), DrawOrder(drawOrder) {}

		void Render() override {
			TransformComponent* t = Owner->GetComponentOfType<TransformComponent>();
			assert(t != nullptr, "trying to render something without a transform?!");

			math::Vector2 textureScaleVec(texture->GetWidth(), texture->GetHeight());
			
			if (FlipHorizontal) {
				textureScaleVec.x *= -1;
			}

			if (FlipVertical) {
				textureScaleVec.y *= -1;
			}

			math::Matrix4 textureScale = math::Matrix4::CreateScale(textureScaleVec);
			math::Matrix4 transformMatrix = textureScale * t->GetTransformMatrix();
			Renderer::Draw(transformMatrix, texture);
		}
	};
}