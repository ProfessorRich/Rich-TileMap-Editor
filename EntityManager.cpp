#include "EntityManager.h"

EntityManager::EntityManager(int mapWidthInTiles, int mapHeightInTiles, int tileSize) {
	m_mapWidthInTiles = mapWidthInTiles;
	m_mapHeightInTiles = mapHeightInTiles;
	m_tileSize = tileSize;
	
	Init();
}

void EntityManager::Init() {
	m_2dEntities.resize(m_mapHeightInTiles);

	for (int i = 0; i < m_mapHeightInTiles; i++) {
		m_2dEntities.at(i).resize(m_mapWidthInTiles);
		for (int j = 0; j < m_mapWidthInTiles; j++) {
			Entity* newEntity = new Entity(*this, "void");

			m_2dEntities.at(i).at(j) = newEntity;
		}
	}
}

void EntityManager::ClearData()
{
	for (auto& entity : m_GUIentities)
	{
		entity->Destroy();
	}

	for (auto& entities : m_2dEntities)
	{
		for (auto& entity : entities) {
			entity->Destroy();
		}
	}
}

void EntityManager::Update(float deltaTime)
{
	for (unsigned int i = 0; i < m_GUIentities.size(); i++) {
		if (!m_GUIentities.at(i)->GetIsActive()) {
			m_GUIentities.erase(m_GUIentities.begin() + i);
		}
		else {
			m_GUIentities.at(i)->Update(deltaTime);
		}
	}

	for (unsigned int i = 0; i < m_2dEntities.size(); i++) {
		for (unsigned int j = 0; j < m_2dEntities.at(i).size(); j++) {
			if (!m_2dEntities.at(i).at(j)->GetIsActive()) {
				m_2dEntities.at(i).erase(m_2dEntities.at(i).begin() + j);
			}
			else {
				m_2dEntities.at(i).at(j)->Update(deltaTime);
			}
		}
	}
}

void EntityManager::Render(SDL_Renderer* theRenderer) const 
{
	for (auto& entities : m_2dEntities) 
	{
		for (auto& entity : entities) {
			entity->Render(theRenderer);
		}
	}

	// Renders SECOND in order to be ON TOP
	for (auto& entity : m_GUIentities)
	{
		entity->Render(theRenderer);
	}
}


void EntityManager::Destroy() 
{
	for (auto& entity : m_GUIentities)
	{
		entity->Destroy();
	}

	for (auto& entities : m_2dEntities) 
	{
		for (auto& entity : entities) {
			entity->Destroy();
		}
	}
}

bool EntityManager::HasNoGUIEntities() const
{
	return m_GUIentities.size() == 0;
}

bool EntityManager::HasNoEntities() const
{
	return m_2dEntities.size() == 0;
}

Entity& EntityManager::AddGUIEntity(std::string entityName) {
	Entity* entity = new Entity(*this, entityName);
	m_GUIentities.emplace_back(entity);

	return *entity;
}

Entity& EntityManager::AddEntity(std::string entityName, int destinationColumn, int destinationRow) {
	Entity* entity = new Entity(*this, entityName);
	m_2dEntities.at(destinationRow).at(destinationColumn) = entity;
	return *entity;
}

std::vector<std::vector<Entity*>> EntityManager::GetEntities() const {
	return m_2dEntities;
}

int EntityManager::GetWidth() const {
	return m_mapWidthInTiles;
}

int EntityManager::GetHeight() const {
	return m_mapHeightInTiles;
}

int EntityManager::GetTileSize() const {
	return m_tileSize;
}

void EntityManager::ListAllEntities() const {
	/*
	for (auto& entities : m_2dEntities) 
	{
		for (auto& entity : entities)
		{
			std::cout << "Entity Name: " << entity->GetName() << std::endl;
			entity->ListAllComponents();
			std::cout << std::endl;
		}
	}*/
}

void EntityManager::InitPosTrackTextComp(TextComponent* pTTC) {
	m_posTrackTextComp = pTTC;
}

void EntityManager::SetPosTrackTextComp(int x, int y) {
	std::stringstream ssPosString;
	ssPosString << "Position: " << "(" << x << "," << y << ")";
	std::string posString = ssPosString.str();
	m_posTrackTextComp->ChangeText(posString);
}

void EntityManager::SetSelectorTransComp(TransformComponent* sTC) {
	m_selectorTransComp = sTC;
}

TransformComponent* EntityManager::GetSelectorTransComp() {
	return m_selectorTransComp;
}