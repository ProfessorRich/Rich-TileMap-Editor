#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* manager) : g_entityManager(manager) {

}

void AssetManager::ClearData() {
	m_textures.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath, SDL_Renderer* theRenderer) {
	m_textures.emplace(textureId, TextureManager::LoadTexture(filePath, theRenderer));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
	return m_textures.at(textureId);
}
