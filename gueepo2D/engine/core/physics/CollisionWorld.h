#pragma once

namespace gueepo {

	namespace math {
		class rect;
	}

	class LineSegment;
	class BoxCollider;
	class Texture;

	struct CollisionData {
		BoxCollider* a;
		BoxCollider* b;

		bool operator==(const CollisionData& other) {
			return (this->a == other.a && this->b == other.b)
				|| (this->a == other.b && this->b == other.a);
		}

		bool Contains(BoxCollider* collider) {
			return (this->a == collider || this->b == collider);
		}
	};

	class CollisionWorld {
	public:
		CollisionWorld();
		~CollisionWorld();

		void Initialize();
		void Debug_Render();
		void Shutdown();

		void Update();

		static bool CheckCollision(const math::rect& rectA, const math::rect& rectB);
		static bool CheckLineCollision(const LineSegment& l, const math::rect& rectA, float& outT);

		void Internal_AddCollider(BoxCollider* b);
		static void AddCollider(BoxCollider* b);

		void Internal_RemoveCollider(BoxCollider* b);
		static void RemoveCollider(BoxCollider* b);
	private:
		static CollisionWorld* s_Instance;
		std::vector<BoxCollider*> m_worldColliders;
		Texture* m_debugTex; // todo: maybe this shouldn't be here?
		
		std::vector<CollisionData> m_LastFrameCollision;
	};
}