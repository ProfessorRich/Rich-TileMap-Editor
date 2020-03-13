#pragma once

#include <vector>
#include <string>
#include <map>

#include "Component.h"

class EntityManager;
class Component;

class Entity
{
private:
	EntityManager& g_entityManager;
	std::vector<Component*> m_components;
	std::map<const std::type_info*, Component*> m_componentTypeMap;
	bool m_isActive;

public:
	Entity(EntityManager& manager);

	void Destroy();

	void Update(float deltaTime);
	void Render(SDL_Renderer*);

	bool GetIsActive();

	// I don't really understand template syntax... but the idea here is that whatever type of component is 'added' by AddComponent, this will deal with it.
	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->g_owner = this;
		m_components.emplace_back(newComponent);
		m_componentTypeMap[&typeid(*newComponent)] = newComponent;
		newComponent->Initialise();
		return *newComponent;
	}

	template <typename T>
	T* GetComponent() {
		if (HasComponent<T>()) {
			return static_cast<T*>(m_componentTypeMap.at(&typeid(T)));					// so ugly and very hard to understand. It gets the component typeid from the map.
		}
		else {
			std::cerr << "Error: Component not found in entity!" << std::endl;
		}
	}

	template <typename T>
	bool HasComponent() const {
		return m_componentTypeMap.count(&typeid(T));
	}
};

