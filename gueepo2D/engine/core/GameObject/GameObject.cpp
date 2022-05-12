#include "gueepo2Dpch.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

namespace gueepo {

	GameObject::GameObject(Texture* t, const std::string& name) : Entity(name) {
		transform = &(AddComponent<TransformComponent>(math::vec2(0.0f, 0.0f), 0.0f, math::vec2(1.0f, 1.0f)));
		sprite = &(AddComponent<SpriteComponent>(t));
	}

	void GameObject::SetTexture(Texture* t) {
		sprite->texture = t;
	}
	void GameObject::SetPosition(float x, float y)	{ transform->SetPosition(x, y);		}
	void GameObject::SetPosition(math::vec2 pos)	{ transform->SetPosition(pos);		}
	void GameObject::Translate(float dx, float dy)	{ transform->Translate(dx, dy);		}
	void GameObject::Translate(math::vec2 ds)		{ transform->Translate(ds);			}
	void GameObject::SetScale(float x, float y)		{ transform->SetScale(x, y);		}
}