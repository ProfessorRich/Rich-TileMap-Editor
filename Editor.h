#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <glm.hpp>
#include <sol.hpp>

// Since this is the main thread, the includes are in the cpp rather than header so it can proc. 
// I just read my above comment and I have no idea wtf it means... but I'll live with it.
#include "EntityManager.h"  

class AssetManager; 

class Editor {
private:
	SDL_Window* m_window;

	TTF_Font* m_GUIFont;

	bool m_isRunning;
	int m_ticksLastFrame = 0;

	int m_selectorX, m_selectorY;

	std::string m_currentTileToPaint;

public:
	SDL_Renderer* g_renderer;
	static AssetManager* g_assetManager;
	static SDL_Event g_event;
	static SDL_Rect g_camera;
	Entity* g_selector;
	   
	Editor();
	~Editor();

	void ProcessInput();
	void MoveCamera(std::string direction);

	void Initialise();
	void InitialiseGUI();

	void Update();
	void Render();

	void RenderClearScreen();

	bool GetIsRunning() const;

	void InitAllMapTiles();
	void PlaceATile(int xTiles, int yTiles, int tileSize, int scale, std::string entityName);
	glm::ivec2 FindSourceTile(std::string entityName);

	void InputATileToPaint();
	void ChooseTileToPaint(std::string sourceTileXY);
};

