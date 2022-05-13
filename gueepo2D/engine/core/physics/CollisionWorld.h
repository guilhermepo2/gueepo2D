#pragma once

namespace gueepo {

	namespace math {
		class rect;
	}

	class LineSegment;
	class BoxCollider;
	class Texture;

	class CollisionWorld {
	public:
		CollisionWorld();
		~CollisionWorld();

		void Initialize();
		void Debug_Render();
		void Shutdown();

		static bool CheckCollision(const math::rect& rectA, const math::rect& rectB);
		static bool CheckLineCollision(const LineSegment& l, const math::rect& rectA, float& outT);

		void Internal_AddCollider(BoxCollider* b);
		static void AddCollider(BoxCollider* b);
	private:
		static CollisionWorld* s_Instance;
		std::vector<BoxCollider*> m_worldColliders;
		Texture* m_debugTex; // todo: maybe this shouldn't be here?
		// todo: last frame collisions?
	};
}