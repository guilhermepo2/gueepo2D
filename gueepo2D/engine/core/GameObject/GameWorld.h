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
		void Kill(Entity* entity);

		int GetNumberOfEntities() const { return m_AllEntities.size(); }

	private:
		std::vector<Entity*> m_AllEntities;
		std::vector<Entity*> m_EntitiesToBeAdded;
		std::vector<Entity*> m_entitiesToBeRemoved;

		void Internal_Update(float DeltaTime);
	};
}