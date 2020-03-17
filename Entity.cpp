#include "Entity.h"

Entity::Entity(EntityManager& manager, std::string name) : g_entityManager(manager), m_name(name) {
	m_isActive = true;
}

void Entity::Destroy() {
	// TODO - DESTROY
}

void Entity::Update(float deltaTime) {
	for (auto& component : m_components) {
		component->Update(deltaTime);
	}
}

void Entity::Render(SDL_Renderer* theRenderer) {
	for (auto& component : m_components) {
		component->Render(theRenderer);
	}
}

bool Entity::GetIsActive() {
	return m_isActive;
}

std::string Entity::GetName() {
	return m_name;
}


void Entity::ListAllComponents() const {

	for (auto& component : m_componentTypeMap) {
		std::cout << "	" << component.first->name() << "\n";
	}

	return;
}