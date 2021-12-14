#include "gueepo2Dpch.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

namespace gueepo {

	GameObject::GameObject(Texture* t, const std::string& name) : Entity(name) {
		transform = &(AddComponent<TransformComponent>(math::Vector2(0.0f, 0.0f), 0.0f, math::Vector2(1.0f, 1.0f)));
		sprite = &(AddComponent<SpriteComponent>(t));
	}

	void GameObject::SetTexture(Texture* t) {
		sprite->texture = t;
	}

	void GameObject::SetPosition(math::Vector2 pos) {
		transform->position = pos;

	}

	void GameObject::Translate(float dx, float dy) {
		transform->position.x += dx;
		transform->position.y += dy;
	}

	void GameObject::Translate(math::Vector2 ds) {
		Translate(ds.x, ds.y);
	}

	void GameObject::SetScale(float x, float y) {
		transform->scale.x = x;
		transform->scale.y = y;
	}

}