#include "gueepo2Dpch.h"
#include "GameWorld.h"

#include "Entity.h"
#include "GameObject.h"

namespace gueepo {

	GameWorld::GameWorld() {}
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

	void GameWorld::Kill(Entity* entity) {
		m_entitiesToBeRemoved.push_back(entity);
	}

	void GameWorld::Internal_Update(float DeltaTime) {
		for(auto entity: m_EntitiesToBeAdded) {
			m_AllEntities.push_back(entity);
		}
		m_EntitiesToBeAdded.clear();

		// #todo: I'm not sure this will actually DELETE the individual element?
		for (auto entity : m_entitiesToBeRemoved) {
			auto toRemove = std::find(m_AllEntities.begin(), m_AllEntities.end(), entity);

			if (toRemove != m_AllEntities.end()) {
				m_AllEntities.erase(toRemove);
			}

			entity->Destroy();
			delete entity;
		}

		m_entitiesToBeRemoved.clear();
	}

}