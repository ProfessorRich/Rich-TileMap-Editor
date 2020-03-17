#pragma once 

#include <SDL.h>
#include <iostream>
#include <glm.hpp>

#include "EntityManager.h"
#include "Editor.h"
								
class TransformComponent : public Component {
public:
	glm::vec2 g_position;
	int g_width;
	int g_height;
	int g_scale;

	TransformComponent(int posX, int posY, int width, int height, int scale) {
		g_position = glm::vec2(posX, posY);
		g_width = width;
		g_height = height;
		g_scale = scale;
	}

	// Theoretically Transform is the first to initialise - always.
	void Initialise() {
	}

	void Update(float deltaTime) {
		// Clamps entity to boundaries (such as the map...)
		if (g_position.x < 0) {
			g_position.x = 0;
		}
		if (g_position.x > G_MAP_WIDTH*G_TILESIZE) {
			g_position.x = G_MAP_WIDTH*G_TILESIZE;
		}
		if (g_position.y < 0) {
			g_position.y = 0;
		}
		if (g_position.y > ((G_MAP_HEIGHT-1)*G_TILESIZE)) {
			g_position.y = ((G_MAP_HEIGHT-1)*G_TILESIZE);
		}
	}

	

	void Render() {
																						// overridden by SpriteComponent
	}

};
