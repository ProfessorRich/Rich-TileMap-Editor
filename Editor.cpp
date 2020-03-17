#include <iostream>
#include <glm.hpp>
#include <sol.hpp>

#include "Editor.h"
#include "AssetManager.h"
#include "Constants.h"
#include "EntityManager.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "Entity.h"
#include "InputControlComponent.h"

EntityManager g_entityManager = EntityManager(G_MAP_WIDTH, G_MAP_HEIGHT, 32);
AssetManager* Editor::g_assetManager = new AssetManager(&g_entityManager);
SDL_Rect Editor::g_camera = { 0,0,G_WINDOW_WIDTH, G_WINDOW_HEIGHT };
SDL_Event Editor::g_event;

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::ProcessInput() {
    SDL_PollEvent(&g_event);

    switch (g_event.type) {
    case SDL_QUIT: {
        m_isRunning = false;
        break;
    }
    case SDL_KEYDOWN: {
        if (g_event.key.keysym.sym == SDLK_ESCAPE) {
            m_isRunning = false;
        }
        if (g_event.key.keysym.sym == SDLK_UP) {
            MoveCamera(std::string("up"));
        }
        if (g_event.key.keysym.sym == SDLK_RIGHT) {
            MoveCamera(std::string("right"));
        }
        if (g_event.key.keysym.sym == SDLK_DOWN) {
            MoveCamera(std::string("down"));
        }
        if (g_event.key.keysym.sym == SDLK_LEFT) {
            MoveCamera(std::string("left"));
        }
        /*if (g_event.key.keysym.sym == SDLK_SPACE) {
            PlaceATile(m_selectorX, m_selectorY, G_TILESIZE, G_SCALE, m_currentTileToPaint);  //TODO Choose tile
        }*/
        if (g_event.key.keysym.sym == SDLK_SPACE) {
            InputATileToPaint();
        }
        else {
            g_selector->GetComponent<InputControlComponent>()->ProcessInput(std::to_string(g_event.key.keysym.sym));
        }
    }
    default: {
        break;
    }
    }
}

void Editor::MoveCamera(std::string direction) {
    if (direction.compare("up") == 0) {
        g_camera.y -= 15;
    }
    if (direction.compare("right") == 0) {
        g_camera.x += 15;
    }
    if (direction.compare("down") == 0) {
        g_camera.y += 15;
    }
    if (direction.compare("left") == 0) {
        g_camera.x -= 15;
    }
}



void Editor::Initialise()
{
    m_selectorX = m_selectorY = 0;
    m_currentTileToPaint = "brush1";

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

    m_window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        G_WINDOW_WIDTH,
        G_WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if (!m_window) 
    {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    g_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (!g_renderer) 
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    m_isRunning = true;

    InitialiseGUI();

    InitAllMapTiles();

    g_entityManager.ListAllEntities();

    return;
}

void Editor::InitialiseGUI() {
    m_GUIFont = TTF_OpenFont("sitka.ttc", 12);

    g_assetManager->AddTexture("basic-tileset", ".\\tilesets\\basic.png", g_renderer);
    
    int toolbarWidth = 10 * 32;
    int toolbarHeight = 3 * 32;
    int toolbarTilesize = 32;
    int toolbarScale = 1;
    int toolbarRows = toolbarHeight / toolbarTilesize;
    int toolbarColumns = toolbarWidth / toolbarTilesize;
    glm::vec2 toolbarPosition = {
        (G_WINDOW_WIDTH / 2) - (toolbarWidth / 2),
        (G_WINDOW_HEIGHT - toolbarHeight)
    };

    for (int i = 0; i < toolbarRows; i++) {
        for (int j = 0; j < toolbarColumns; j++) {

            Entity& toolbar = g_entityManager.AddGUIEntity("toolbar icon");
            toolbar.AddComponent<TransformComponent>(toolbarPosition.x + j * toolbarTilesize, toolbarPosition.y + i * toolbarTilesize, toolbarTilesize, toolbarTilesize, toolbarScale);
            toolbar.AddComponent<SpriteComponent>("basic-tileset", toolbarTilesize, i, j, true);
        }
    }

    Entity& overlay = g_entityManager.AddGUIEntity("overlay");

    for (int i = 0; i < toolbarRows; i++) {
        for (int j = 0; j < toolbarColumns; j++) {
            std::string printString = std::to_string(i) + std::to_string(j);
            overlay.AddComponent<TextComponent>(toolbarPosition.x + (j*toolbarTilesize), toolbarPosition.y + (i*toolbarTilesize), printString, G_WHITE_COLOUR, g_renderer, m_GUIFont);
        }
    }

    Entity& posTracker = g_entityManager.AddGUIEntity("position");

    posTracker.AddComponent<TextComponent>(G_WINDOW_WIDTH - 100, 0, "wait", G_WHITE_COLOUR, g_renderer, m_GUIFont);

    g_entityManager.InitPosTrackTextComp(posTracker.GetComponent<TextComponent>());

    g_assetManager->AddTexture("selector", ".\\tilesets\\selector.png", g_renderer);

    g_selector = &g_entityManager.AddGUIEntity("selector");
    g_selector->AddComponent<TransformComponent>(0, 0, toolbarTilesize, toolbarTilesize, toolbarScale);
    g_selector->AddComponent<SpriteComponent>("selector", toolbarTilesize, 0,0,false, true, 2);
    g_selector->AddComponent<InputControlComponent>();

    g_entityManager.SetSelectorTransComp(g_selector->GetComponent<TransformComponent>());
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

    m_selectorX = g_entityManager.GetSelectorTransComp()->g_position.x / 32;
    m_selectorY = g_entityManager.GetSelectorTransComp()->g_position.y / 32;

    g_entityManager.SetPosTrackTextComp(m_selectorX, m_selectorY);
}

// Get everything to render in the SDL buffer, then swap it with the screen.
void Editor::Render()
{
    RenderClearScreen();

    // Render some game stuff in the buffer  w/ all new code which prevents horrible CPU breaking loops when there are no entities.
    if (g_entityManager.HasNoGUIEntities()) {
        std::cerr << "No GUI entities detected. Any ideas why that might be Sherlock?" << std::endl;
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

// Put default tiles over the map width and height
void Editor::InitAllMapTiles() {

    for (int i = 0; i < g_entityManager.GetHeight(); i++) {
        for (int j = 0; j < g_entityManager.GetWidth(); j++) {

            PlaceATile(j, i, g_entityManager.GetTileSize(), 1, "brush0");
        }
    }
}

// Create an entity to become a tile at the correct location with appropriate components
void Editor::PlaceATile(int x, int y, int tileSize, int scale, std::string entName) {
    int pixelX = x * tileSize;
    int pixelY = y * tileSize;

    Entity& newEntity = g_entityManager.AddEntity(entName, x, y);

    newEntity.AddComponent<TransformComponent>(pixelX, pixelY, tileSize, tileSize, scale);

    glm::ivec2 textureSourceCoord = FindSourceTile(entName);
    newEntity.AddComponent<SpriteComponent>("basic-tileset", tileSize, textureSourceCoord.x, textureSourceCoord.y);
}

// Take an entity name and find where the right pixel art is in the basic-tileset for the map

glm::ivec2 Editor::FindSourceTile(std::string entityName) {
    if (entityName.compare("brush0") == 0) {
        return { 0, 0 };
    }

    if (entityName.compare("brush1") == 0) {
        return { 0, 1 };
    }

    // TODO - implement
    
}

void Editor::InputATileToPaint() {
    SDL_Event event;

    SDL_StartTextInput();
    SDL_bool done = SDL_FALSE;

    std::string text; //TODO FIX ALL THIS TOTAL SHIT!

    while (!done) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                /* Quit */
                done = SDL_TRUE;
                break;
                /*case SDL_TEXTINPUT:
                    // Add new text onto the end of our text
                    text += event.text.text;
                    system("cls");
                    std::cout << text << std::endl;
                    break;
                }*/
            case SDL_KEYDOWN:
                if (SDL_GetKeyName(event.key.keysym.sym) == "Escape") {
                    done = SDL_TRUE;
                    return;
                }
            }
        }
    }

    SDL_StopTextInput();
}

void Editor::ChooseTileToPaint(std::string sourceTileXY) {
    m_currentTileToPaint = "brush" + sourceTileXY;
}