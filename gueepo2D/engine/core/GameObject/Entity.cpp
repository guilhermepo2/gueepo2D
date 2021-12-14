#include "gueepo2Dpch.h"
#include "Entity.h"
#include "Component.h"

gueepo::Entity::Entity() : m_bIsActive(true), Name("Entity") {}

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
}

void gueepo::Entity::Render() {
	for (Component* c : m_Components) {
		c->Render();
	}
}

void gueepo::Entity::Destroy() {
	for (Component* c : m_Components) {
		c->Destroy();
	}
	// todo: properly destroy/mark for destruction
	m_bIsActive = false;
}


