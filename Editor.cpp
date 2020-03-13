#include "Editor.h"

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::Initialise()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    if (TTF_Init() != 0) {
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

    if (!m_window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    g_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (!g_renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    m_isRunning = true;

    return;
}

void Editor::Update()
{
}

void Editor::Render()
{

    exit(0);
}

bool Editor::GetIsRunning() const {
    return m_isRunning;
}