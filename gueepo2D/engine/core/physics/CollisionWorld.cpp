#include "gueepo2Dpch.h"
#include "CollisionWorld.h"
#include "LineSegment.h"
#include "core/math/math.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/Texture.h"
#include "core/GameObject/BoxCollider.h"
#include "core/GameObject/Entity.h"
#include "core/GameObject/TransformComponent.h"

namespace gueepo {

	CollisionWorld* CollisionWorld::s_Instance = nullptr;

	CollisionWorld::CollisionWorld() {}
	CollisionWorld::~CollisionWorld() {}


	void CollisionWorld::Initialize() {
		if (s_Instance != nullptr) {
			LOG_ERROR("are you trying to create two collision worlds?");
			return;
		}

		s_Instance = this;

		// TODO: YOINK THIS FROM HERE!!
		m_debugTex = Texture::Create(4, 4);
		uint32_t* mydata = new uint32_t[4 * 4];
		for (int i = 0; i < 4 * 4; i ++) {
			mydata[i] =
				((155 & 0xFF) << 24) +
				((0) << 16) +
				((0) << 8) +
				((255 & 0xFF));
		}
		m_debugTex->SetData(mydata, 4 * 4 * sizeof(uint32_t));
		delete[] mydata;
	}

	void CollisionWorld::Debug_Render() {
		// there's something wrong with rendering colliders like
		// therefore, interpreting rects like this when treating collisions will also lead to incorrect collisions
		// the thing is that, for example, having a collider with a rect (-8.0f, -8.0f) (8.0f, 8.0f), and (0.0f, 0.0f) (16.0f) (16.0f) are two very different things
		// even though the size is the same

		for (int i = 0; i < m_worldColliders.size(); i++) {
			math::vec2 bottomLeft = m_worldColliders[i]->collisionRect.bottomLeft;
			math::vec2 topRight = m_worldColliders[i]->collisionRect.topRight;

			math::vec2 textureScale = m_worldColliders[i]->collisionRect.GetSize();
			math::mat4 textureScaleM = math::mat4::CreateScale(textureScale);

			// there's so many layers of wrong things on the line below
			TransformComponent* transform = m_worldColliders[i]->Owner->GetComponentOfType<TransformComponent>();
			math::vec2 position = transform->position;
			// my current guess on how to handle things correctly is to translate the position by half the size?
			position.x += (textureScale.x / 2) * transform->scale.x;
			position.y += (textureScale.y / 2) * transform->scale.y;
			// and then substracting the min?
			position.x += (bottomLeft.x) * transform->scale.x;
			position.y += (bottomLeft.y) * transform->scale.y;

			math::mat4 transformMatrix = textureScaleM * math::mat4::CreateScale(transform->scale) * math::mat4::CreateTranslation(position);
			gueepo::Renderer::Draw(transformMatrix, m_debugTex);
		 }
	}

	void CollisionWorld::Shutdown() {
		// destroy all colliders (if any) and clear data structures
	}

	void CollisionWorld::Internal_AddCollider(BoxCollider* b) {
		m_worldColliders.push_back(b);
	}

	void CollisionWorld::Internal_RemoveCollider(BoxCollider* b) {
		// just remove the pointer, not sure if sounds weird or not but it's not up to the CollisionWorld to guarantee BoxCollider resources were freed
		// BoxCollider is a component, so that's up to the ECS system.
		std::vector<BoxCollider*>::iterator collider = std::find(m_worldColliders.begin(), m_worldColliders.end(), b);

		if (collider != m_worldColliders.end()) {
			std::iter_swap(collider, m_worldColliders.end() - 1);
			m_worldColliders.pop_back();
		}

	}

	// =====================================================================
	// static implementations
	// =====================================================================
	bool CollisionWorld::CheckCollision(const math::rect& rectA, const math::rect& rectB) {
		bool NotIntersected =
			rectA.topRight.x < rectB.bottomLeft.x ||
			rectA.topRight.y < rectB.bottomLeft.y ||
			rectB.topRight.x < rectA.bottomLeft.x ||
			rectB.topRight.y < rectA.bottomLeft.y;

		return !NotIntersected;
	}

	bool CollisionWorld::CheckLineCollision(const LineSegment& l, const math::rect& rectA, float& outT) {
		float steps = 0.05f;

		for (float i = 0.0f; i <= 1.0f; i += steps) {
			if (rectA.Contains(l.PointOnSegment(i))) {
				outT = i;
				return true;
			}
		}

		return false;
	}

	void CollisionWorld::AddCollider(BoxCollider* b) {
		g2dassert(s_Instance != nullptr, "can't add collider if collision world wasn't created!");
		s_Instance->Internal_AddCollider(b);
	}

	void CollisionWorld::RemoveCollider(BoxCollider* b) {
		g2dassert(s_Instance != nullptr, "can't remove a collider if collision world wasn't created!");
		s_Instance->Internal_RemoveCollider(b);
	}

}