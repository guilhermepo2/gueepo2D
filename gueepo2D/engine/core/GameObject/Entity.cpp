#include "gueepo2Dpch.h"
#include "Entity.h"
#include "Component.h"
#include "core/Log.h"
#include "GameWorld.h"

gueepo::Entity::Entity() : m_bIsActive(true), m_bHasLifetime(false), Name("Entity") {}
gueepo::Entity::Entity(const std::string& name) : m_bIsActive(true), Name(name) {}

void gueepo::Entity::BeginPlay() {
	for (Component* c : m_Components) {
		c->BeginPlay();
	}
}

bool gueepo::Entity::ProcessInput(const InputState& CurrentInputState) {
	for (Component* c : m_Components) {
		if (c->ProcessInput(CurrentInputState)) {
			return true;
		}
	}

	return false;
}

void gueepo::Entity::Update(float DeltaTime) {
	for (Component* c : m_Components) {
		c->Update(DeltaTime);
	}

	if (m_bHasLifetime) {

		if (lifetime < 0.0f) {
			GameWorld::Kill(this);
		}

		lifetime -= DeltaTime;
	}
}

void gueepo::Entity::Render() {
	for (Component* c : m_Components) {
		c->Render();
	}
}

void gueepo::Entity::Destroy() {
	
	for (int i = 0; i < m_Components.size(); i++) {
		Component* c = m_Components[i];
		c->Destroy();
		delete c;
	}
	
	m_Components.clear();
	m_bIsActive = false;
}


