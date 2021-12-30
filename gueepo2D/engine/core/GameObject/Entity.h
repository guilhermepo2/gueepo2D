/*
* An entity is an empty "gameObject" that server as an abstract base basically
*/

#pragma once
#include <string>
#include <map>
#include <vector>
#include <typeinfo>

namespace gueepo {
	class Component;
	struct InputState;

	class Entity {
	public:
		std::string Name;
		Entity();
		Entity(const std::string& name);

		inline bool IsActive() const { return m_bIsActive; }
	private:
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