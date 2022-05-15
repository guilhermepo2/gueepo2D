#include "gueepo2Dpch.h"
#include "GameWorld.h"

#include "Entity.h"
#include "GameObject.h"

namespace gueepo {

	GameWorld* GameWorld::s_instance = nullptr;

	GameWorld::GameWorld() {
		if (s_instance != nullptr) {
			LOG_ERROR("trying to create a second instance of the game world?!");
			return;
		}

		s_instance = this;
	}

	GameWorld::~GameWorld() {}

	void GameWorld::BeginPlay() {
		for (auto entity : m_AllEntities) {
			entity->BeginPlay();
		}
	}

	void GameWorld::ProcessInput(const InputState& CurrentInputState) {
		for (auto entity : m_AllEntities) {
			entity->ProcessInput(CurrentInputState);
		}
	}

	void GameWorld::Update(float DeltaTime) {
		for (auto entity : m_AllEntities) {
			entity->Update(DeltaTime);
		}

		Internal_Update(DeltaTime);
	}

	void GameWorld::Render() {
		for (auto entity : m_AllEntities) {
			entity->Render();
		}
	}

	void GameWorld::Destroy() {
		for (auto entity : m_AllEntities) {
			entity->Destroy();
		}
	}

	Entity* GameWorld::CreateEntity(const std::string& name) {
		Entity* newEntity = new Entity(name);
		m_EntitiesToBeAdded.push_back(newEntity);
		return newEntity;
	}

	gueepo::GameObject* GameWorld::CreateGameObject(Texture* tex, const std::string& name /*= "GameObject"*/) {
		GameObject* newGameObject = new GameObject(tex, name);
		m_EntitiesToBeAdded.push_back(newGameObject);
		return newGameObject;
	}

	void GameWorld::KillEntity(Entity* entity) {
		m_entitiesToBeRemoved.push_back(entity);
	}

	void GameWorld::Internal_Update(float DeltaTime) {
		for(auto entity: m_EntitiesToBeAdded) {
			m_AllEntities.push_back(entity);
		}
		m_EntitiesToBeAdded.clear();

		for (auto entity : m_entitiesToBeRemoved) {
			if (!entity->IsActive()) {
				// it was already removed!
				LOG_WARN("trying to remove entity that was already removed...");
				continue;
			}

			auto toRemove = std::find(m_AllEntities.begin(), m_AllEntities.end(), entity);

			if (toRemove != m_AllEntities.end()) {
 				std::iter_swap(toRemove, m_AllEntities.end() - 1);
				entity->Destroy();
				delete entity;
				m_AllEntities.pop_back();
			}
		}

		m_entitiesToBeRemoved.clear();
	}


	// =================================================
	// 
	// static implementations
	// 
	// =================================================
	Entity* GameWorld::Create(const std::string& name) {
		g2dassert(s_instance != nullptr, "can't create an entity without creating a game world!");
		return s_instance->CreateEntity(name);
	}

	void GameWorld::Kill(Entity* entity) {
		g2dassert(s_instance != nullptr, "can't destroy an entity without creating a game world!");
		s_instance->KillEntity(entity);
	}
}