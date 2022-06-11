#include "gueepo2Dpch.h"
#include "CollisionWorld.h"
#include "LineSegment.h"
#include "core/math/math.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/SpriteBatcher.h"
#include "core/renderer/Texture.h"
#include "core/GameObject/BoxCollider.h"
#include "core/GameObject/Entity.h"
#include "core/GameObject/TransformComponent.h"


namespace gueepo {

	bool Contains(BoxCollider* b) {
		return false;
	}

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
			gueepo::Renderer::s_spriteBatcher->Draw(transformMatrix, m_debugTex);
		 }
	}

	void CollisionWorld::Shutdown() {
		m_LastFrameCollision.clear();
		m_worldColliders.clear();
	}

	void CollisionWorld::Update() {
		std::vector<CollisionData> collisionsThisFrame;

		// check for all collisions
		for (int i = 0; i < m_worldColliders.size(); i++) {
			for (int j = i + 1; j < m_worldColliders.size(); j++) {
				BoxCollider* a = m_worldColliders[i];
				BoxCollider* b = m_worldColliders[j];
				math::rect rectA = a->GetWorldPositionRect();
				math::rect rectB = b->GetWorldPositionRect();

				if (CheckCollision(rectA, rectB)) {
					collisionsThisFrame.push_back({ a, b });
				}
			}
		}

		// checking collisions that happened against last frame collisions
		for (int i = 0; i < collisionsThisFrame.size(); i++) {
			// first, dispatch all new collisions to "Handle Collision Callback" anyways
			collisionsThisFrame[i].a->HandleOnCollision(collisionsThisFrame[i].b);
			collisionsThisFrame[i].b->HandleOnCollision(collisionsThisFrame[i].a);

			auto isCollisionRepeated = std::find(m_LastFrameCollision.begin(), m_LastFrameCollision.end(), collisionsThisFrame[i]);

			if (isCollisionRepeated == m_LastFrameCollision.end()) {
				// dispatching on collision enter
				collisionsThisFrame[i].a->HandleOnCollisionEnter(collisionsThisFrame[i].b);
				collisionsThisFrame[i].b->HandleOnCollisionEnter(collisionsThisFrame[i].a);
			}
			else {
				// dispatching on collision stay
				collisionsThisFrame[i].a->HandleOnCollisionStay(collisionsThisFrame[i].b);
				collisionsThisFrame[i].b->HandleOnCollisionStay(collisionsThisFrame[i].a);
			}
		}

		// checking which collisions no longer happen
		for (int i = 0; i < m_LastFrameCollision.size(); i++) {
			auto collisionNoLongerHappens = std::find(collisionsThisFrame.begin(), collisionsThisFrame.end(), m_LastFrameCollision[i]);

			if (collisionNoLongerHappens == collisionsThisFrame.end()) {
				if (m_LastFrameCollision[i].a != nullptr && m_LastFrameCollision[i].b != nullptr) {
					m_LastFrameCollision[i].a->HandleOnCollisionExit(m_LastFrameCollision[i].b);
					m_LastFrameCollision[i].b->HandleOnCollisionExit(m_LastFrameCollision[i].a);
				}
			}
		}

		m_LastFrameCollision.clear();
		m_LastFrameCollision = collisionsThisFrame;

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

		// we also have to remove all collisions this collider was envolved in!!
		// doing this the lazy way. I will just create another vector of collisions.
		std::vector<CollisionData> newCollisionData;
		for (int i = 0; i < m_LastFrameCollision.size(); i++) {
			if (!m_LastFrameCollision[i].Contains(b)) {
				newCollisionData.push_back(m_LastFrameCollision[i]);
			}
		}

		m_LastFrameCollision.clear();
		m_LastFrameCollision = newCollisionData;
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