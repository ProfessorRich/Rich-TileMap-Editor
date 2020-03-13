#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Constants.h"

class Editor {
private:
	SDL_Window* m_window;

	bool m_isRunning;

public:
	SDL_Renderer* g_renderer;

	Editor();
	~Editor();

	void Initialise();

	void Update();
	void Render();

	bool GetIsRunning() const;
};

