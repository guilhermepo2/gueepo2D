// =================================================================================
// GameObject.h
// 
// A GameObject is just an entity with a transform component and a sprite component
// 
// =================================================================================

#pragma once
#include "Entity.h"
#include "core/math/Math.h"

namespace gueepo {
	class TransformComponent;
	class SpriteComponent;
	class Texture;

	class GameObject : public Entity {
	public:
		GameObject(Texture* t, const std::string& name = "GameObject");
		TransformComponent* transform;
		SpriteComponent* sprite;

		void SetTexture(Texture* t);
		void SetPosition(float x, float y);
		void SetPosition(math::vec2 pos);
		void Translate(float dx, float dy);
		void Translate(math::vec2 ds);
		void SetScale(float x, float y);
	};
}
