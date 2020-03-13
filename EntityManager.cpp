#include "EntityManager.h"

EntityManager::EntityManager() {

}

void EntityManager::ClearData() 
{
	for (auto& entity : m_entities) 
	{
		entity->Destroy();
	}
}

void EntityManager::Update(float deltaTime) 
{		//TODO - is this working OK??
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		if (!m_entities.at(i)->GetIsActive()) {
			m_entities.erase(m_entities.begin() + i);
		}
		else {
			m_entities.at(i)->Update(deltaTime);
		}
	}
}

void EntityManager::Render(SDL_Renderer* theRenderer) const 
{
	for (auto& entity : m_entities) 
	{
		entity->Render(theRenderer);
	}
}


void EntityManager::Destroy() 
{
	for (auto& entity : m_entities) 
	{
		entity->Destroy();
	}
}

bool EntityManager::HasNoEntities() const
{
	return m_entities.size() == 0;
}
/*
Entity& EntityManager::AddEntity(std::string entityName) {
	Entity* entity = new Entity(*this, entityName);
	m_entities.emplace_back(entity);

	return *entity;
}*/