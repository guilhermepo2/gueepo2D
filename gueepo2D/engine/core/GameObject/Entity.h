/*
* An entity is an empty "gameObject" that serves as an abstract base basically
*/

#pragma once
#include <string>
#include <map>
#include <vector>
#include <typeinfo>

using EntityCallback = std::function<void(void)>;
#define ENTITY_CALLBACK(...) std::bind(__VA_ARGS__, this);

namespace gueepo {
	class Component;
	struct InputState;

	class Entity {
	public:
		std::string Name;
		Entity();
		Entity(const std::string& name);
		~Entity() = default;

		float lifetime;
		void SetLifetime(float lf) { lifetime = lf; m_bHasLifetime = true; }

		inline bool IsActive() const { return m_bIsActive; }

	public:
		// Messages
		EntityCallback OnEntityDestroyed;

	private:
		bool m_bHasLifetime = false;
		bool m_bIsActive;
		std::vector<Component*> m_Components;
		std::map<const std::type_info*, Component*> m_TypeInfoToComponent;

	public:
		void BeginPlay();
		bool ProcessInput(const InputState& CurrentInputState);
		void Update(float DeltaTime);
		void Render();
		void Destroy();

		template<typename T, typename... TArgs>
		T& AddComponent(TArgs&&... Args) {
			T* nc(new T(std::forward<TArgs>(Args)...));
			nc->Owner = this;
			m_Components.push_back(nc);
			m_TypeInfoToComponent[&typeid(*nc)] = nc;
			nc->Initialize();
			return *nc;
		}
		
		template<typename T>
		T* GetComponentOfType() {
			return static_cast<T*>(m_TypeInfoToComponent[&typeid(T)]);
		}

		template<typename T>
		bool HasComponentOfType() const {
			return m_TypeInfoToComponent.count(&typeid(T));
		}
	};
}