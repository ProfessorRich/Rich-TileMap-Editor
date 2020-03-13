#include <iostream>

#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* theRenderer) {
	SDL_Surface* surface = IMG_Load(fileName);
	if (surface == NULL) std::cerr << IMG_GetError() << std::endl;
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(theRenderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destinationRect, SDL_Renderer* theRenderer) {
	SDL_RenderCopyEx(theRenderer, texture, &sourceRect, &destinationRect, 0.0, NULL, SDL_FLIP_NONE);
}

