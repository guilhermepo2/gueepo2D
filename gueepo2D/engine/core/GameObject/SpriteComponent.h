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
		static Shader* defaultSpriteShader;
		static VertexArray* defaultVertexArray;
		static void InitializeDefaults();

	
	public:
		Texture* texture;
		int DrawOrder = 1;
		// todo: color (should be in the material?)
		bool FlipHorizontal = false;
		bool FlipVertical = false;

		SpriteComponent() : texture(nullptr) { InitializeDefaults(); }
		SpriteComponent(Texture* tex, int drawOrder = 1) : texture(tex), DrawOrder(drawOrder) { InitializeDefaults(); }

		void Render() override {
			texture->Bind();
			TransformComponent* t = Owner->GetComponentOfType<TransformComponent>();

			assert(t != nullptr, "trying to render something without a transform?!")

			math::Matrix4 textureScale = math::Matrix4::CreateScale(math::Vector2(texture->GetWidth(), texture->GetHeight()));
			math::Matrix4 transformMatrix = textureScale * t->GetTransformMatrix();
			defaultSpriteShader->SetMat4("u_Transform", transformMatrix);
			// have to set the shader matrix here?!
			Renderer::Submit(defaultVertexArray, defaultSpriteShader);
		}
	};
}