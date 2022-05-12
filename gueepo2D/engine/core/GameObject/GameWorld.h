#pragma once

namespace gueepo {
	
	class Component;
	class Entity;
	class GameObject;
	struct InputState;
	class Texture;

	class GameWorld {
	public:

		GameWorld();
		~GameWorld();

		void BeginPlay();
		void ProcessInput(const InputState& CurrentInputState);
		void Update(float DeltaTime);
		void Render();
		void Destroy();

		Entity* CreateEntity(const std::string& name = "Entity");
		GameObject* CreateGameObject(Texture* tex, const std::string& name = "GameObject");
		void KillEntity(Entity* entity);

		size_t GetNumberOfEntities() const { return m_AllEntities.size(); }

		static Entity* Create(const std::string& name = "Entity");
		static void Kill(Entity* entity);

	private:
		static GameWorld* s_instance;

		std::vector<Entity*> m_AllEntities;
		std::vector<Entity*> m_EntitiesToBeAdded;
		std::vector<Entity*> m_entitiesToBeRemoved;

		void Internal_Update(float DeltaTime);
	};
}