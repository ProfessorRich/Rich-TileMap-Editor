#pragma once

#include <vector>
#include <string>
#include <SDL.h>

#include "Constants.h"
#include "Component.h"
#include "Entity.h"

class ColliderComponent;							

class EntityManager {
private:
	std::vector<Entity*> m_entities;

public:
	EntityManager();

	void ClearData();
	void Update(float deltaTime);
	void Render(SDL_Renderer* theRenderer) const;
	void Destroy();

	bool HasNoEntities() const;

	Entity& AddEntity(std::string entityName);
	
	std::vector<Entity*> GetEntities() const;
	
};