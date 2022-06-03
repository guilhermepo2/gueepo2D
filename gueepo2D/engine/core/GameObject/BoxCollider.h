#pragma once
#include "Component.h"
#include "core/math/math.h"
#include "core/physics/CollisionWorld.h"
#include "core/GameObject/Entity.h"
#include "core/GameObject/TransformComponent.h"

namespace gueepo {
	class BoxCollider : public Component {
	public:
		BoxCollider(const math::vec2& bottomLeft, const math::vec2& topRight) {
			collisionRect.bottomLeft = bottomLeft;
			collisionRect.topRight = topRight;
			CollisionWorld::AddCollider(this);
		}

		~BoxCollider() {
			CollisionWorld::RemoveCollider(this);
		}

		using CollisionCallback = std::function<void(gueepo::BoxCollider*)>;
		#define COLLISION_CALLBACK(...) std::bind(__VA_ARGS__, this, std::placeholders::_1);
		
		// Collision Callbacks
		CollisionCallback OnCollisionEnter;
		void HandleOnCollisionEnter(BoxCollider* other) { if (OnCollisionEnter != nullptr) { OnCollisionEnter(other); } }
		CollisionCallback OnCollisionStay;
		void HandleOnCollisionStay(BoxCollider* other) { if (OnCollisionStay != nullptr) { OnCollisionStay(other); } }
		CollisionCallback OnCollisionExit;
		void HandleOnCollisionExit(BoxCollider* other) { if (OnCollisionExit != nullptr) { OnCollisionExit(other); } }
		CollisionCallback OnCollision;
		void HandleOnCollision(BoxCollider* other) { if (OnCollision != nullptr) { OnCollision(other); } }


		void SetTag(const std::string& tag) { m_tag = tag; }
		const std::string& GetTag() const { return m_tag; }

		const math::rect& GetRect() const { return collisionRect; }
		const math::rect GetWorldPositionRect() const {
			TransformComponent* ownerTransform = Owner->GetComponentOfType<TransformComponent>();
			g2dassert(ownerTransform != nullptr, "owner has a nullptr!?");

			math::vec2 scale = ownerTransform->scale;
			math::vec2 position = ownerTransform->position;

			// todo: copy constructor?
			math::rect t_rect;
			t_rect.bottomLeft = collisionRect.bottomLeft;
			t_rect.topRight = collisionRect.topRight;
			// todo: Expand(x, y) ?
			t_rect.bottomLeft.x *= scale.x;
			t_rect.bottomLeft.y *= scale.y;
			t_rect.topRight.x *= scale.x;
			t_rect.topRight.y *= scale.y;
			// todo: move(x, y)?
			t_rect.bottomLeft += position;
			t_rect.topRight += position;

			return t_rect;
		}
	private:
		friend CollisionWorld;
		math::rect collisionRect;
		std::string m_tag;
	};
}