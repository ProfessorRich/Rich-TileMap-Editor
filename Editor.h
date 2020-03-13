#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <glm.hpp>
#include <sol.hpp>

// Since this is the main thread, the includes are in the cpp rather than header so it can proc.
#include "EntityManager.h"  

// Let's proc that baitch
class AssetManager; 

class Editor {
private:
	SDL_Window* m_window;

	bool m_isRunning;
	unsigned int m_ticksLastFrame;

public:
	SDL_Renderer* g_renderer;
	static AssetManager* g_assetManager;
	static SDL_Event g_event;
	static SDL_Rect g_camera;

	Editor();
	~Editor();

	void Initialise();
	void InitialiseGUI();

	void Update();
	void Render();

	void RenderClearScreen();

	bool GetIsRunning() const;
};

