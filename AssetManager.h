#pragma once

#include <map>
#include <string>
#include <SDL_ttf.h>

#include "TextureManager.h"
#include "EntityManager.h"

class AssetManager {
private:
	EntityManager* g_entityManager;
	std::map<std::string, SDL_Texture*> m_textures;

public:
	AssetManager(EntityManager* manager);
	~AssetManager();

	void ClearData();

	void AddTexture(std::string textureId, const char* filePath, SDL_Renderer* theRenderer);

	SDL_Texture* GetTexture(std::string textureId);
};