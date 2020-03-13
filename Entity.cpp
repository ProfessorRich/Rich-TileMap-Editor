#include "Entity.h"

Entity::Entity(EntityManager& manager) : g_entityManager(manager) {
	
}

void Entity::Destroy() {
	// TODO - DESTROY
}

bool Entity::GetIsActive() {
	return m_isActive;
}

void Entity::Update(float deltaTime) {

}

void Entity::Render(SDL_Renderer* theRenderer) {
	for (auto& component : m_components) {
		component->Render(theRenderer);
	}
}