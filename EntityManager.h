#pragma once

#include <vector>
#include <string>
#include <SDL.h>

#include "Constants.h"
#include "Component.h"
#include "Entity.h"		
#include "TextComponent.h"

class TransformComponent;
class SpriteComponent;

class EntityManager {
private:
	//Separate entities to allow top layer rendering of GUI
	std::vector<Entity*> m_GUIentities;
	std::vector<std::vector<Entity*>> m_2dEntities;

	int m_mapWidthInTiles;
	int m_mapHeightInTiles;
	int m_tileSize;

	TextComponent* m_posTrackTextComp;
	TransformComponent* m_selectorTransComp;

public:
	EntityManager(int mapWidthInTiles, int mapHeightInTiles, int tileSize);

	void Init();

	void ClearData();
	void Update(float deltaTime);
	void Render(SDL_Renderer* theRenderer) const;
	void Destroy();

	bool HasNoGUIEntities() const;
	bool HasNoEntities() const;

	Entity& AddGUIEntity(std::string entityName);
	Entity& AddEntity(std::string entityName, int destCol, int destRow);
	
	std::vector<Entity*> GetGUIEntities() const;
	std::vector<std::vector<Entity*>> GetEntities() const;

	int GetWidth() const;
	int GetHeight() const;
	int GetTileSize() const;

	void ListAllEntities() const;

	void InitPosTrackTextComp(TextComponent* pTTC);
	void SetPosTrackTextComp(int x, int y);

	void SetSelectorTransComp(TransformComponent* sTC);
	TransformComponent* GetSelectorTransComp();
};