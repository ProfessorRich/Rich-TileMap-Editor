#include <iostream>
#include <glm.hpp>
#include <sol.hpp>

#include "Editor.h"
#include "AssetManager.h"
#include "Constants.h"
#include "EntityManager.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

EntityManager g_entityManager;
AssetManager* Editor::g_assetManager = new AssetManager(&g_entityManager);
SDL_Rect Editor::g_camera = { 0,0,G_WINDOW_WIDTH, G_WINDOW_HEIGHT };

Editor::Editor()
{

    m_window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        G_WINDOW_WIDTH,
        G_WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    g_renderer = NULL;
    g_renderer = SDL_CreateRenderer(m_window, -1, 0);

}

Editor::~Editor()
{
}

void Editor::Initialise()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    if (TTF_Init() != 0) 
    {
        std::cerr << "Error initializing SDL_ttf." << std::endl;
        return;
    }

    if (!m_window) 
    {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    if (!g_renderer) 
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    m_isRunning = true;

    return;
}

void InitialiseGUI() {
    // TODO Add Tilemap to bottom

    // TODO Add Numbers on top

}

// Update everything
void Editor::Update()
{
    // Wait till G_TARGET_DELTA_MS passed since m_ticksLastFrame thereby allowing function to loop maximally G_TARGET_FPS times per second.
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), static_cast<float>(m_ticksLastFrame) + G_TARGET_DELTA_MS));

    // How much time in s has passed since last frame?
    float deltaTime = (SDL_GetTicks() - m_ticksLastFrame) / 1000.0f;

    // Clamp the deltaTime to allow for pauses and breaks and prevent timewarping
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    m_ticksLastFrame = SDL_GetTicks();

    // Move entities by proportionally how much deltaTime has passed in s since last frame.
    g_entityManager.Update(deltaTime);
}

// Get everything to render in the SDL buffer, then swap it with the screen.
void Editor::Render()
{
    RenderClearScreen();

    // Render some game stuff in the buffer  w/ all new code which prevents horrible CPU breaking loops when there are no entities.
    if (g_entityManager.HasNoEntities()) {
        std::cerr << "No entities detected. Any ideas why that might be Sherlock?" << std::endl;
        exit(0);
    }
    else {
        g_entityManager.Render(g_renderer);
    }

    // Swap the buffer with what is on screen
    SDL_RenderPresent(g_renderer);
}

// Clear the buffer with a default colour
void Editor::RenderClearScreen() {
    SDL_SetRenderDrawColor(g_renderer, 21, 21, 21, 255);
    SDL_RenderClear(g_renderer);
}

// Return a bool to say if the editor is running
bool Editor::GetIsRunning() const {
    return m_isRunning;
}