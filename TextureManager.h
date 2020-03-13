#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Editor.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer*);
	static void Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_Renderer* theRenderer);
};