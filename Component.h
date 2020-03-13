#pragma once

#include <iostream>
#include <SDL.h>

#include "Entity.h"

// holder class so that this can compile and then Entity and EntityManager can compile after this!
class Entity;	

class Component {
public:
	Entity* g_owner;

	virtual ~Component() {}
	virtual void Initialise() {}
	virtual void Update(float deltaTime) {}
	virtual void Render(SDL_Renderer*) {}
};