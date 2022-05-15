#pragma once
#include "Component.h"
#include "core/math/math.h"
#include "core/physics/CollisionWorld.h"

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

		void SetTag(const std::string& tag) { m_tag = tag; }
		const std::string& GetTag() const { return m_tag; }
	private:
		friend CollisionWorld;
		math::rect collisionRect;
		std::string m_tag;
	};
}