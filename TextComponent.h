#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "EntityManager.h"
#include "AssetManager.h"
#include "Editor.h"

class TextComponent : public Component{
private:
	SDL_Rect m_position;
	std::string m_textContent;
	SDL_Colour m_colour; 
	SDL_Texture* m_texture;

	SDL_Renderer* m_renderer;

	TTF_Font* m_font;

public:
	TextComponent(int x, int y, std::string textContent, const SDL_Colour colour, SDL_Renderer* renderer, TTF_Font* font) {
		m_position.x = x;
		m_position.y = y;
		m_textContent = textContent;
		m_colour = colour;
		m_renderer = renderer;

		m_font = font;

		PrepareText(m_font);
	}
	
	// TODO - make safer. Shouldn't crash if can't find font ID!
	void PrepareText(TTF_Font* font) {
		SDL_Surface* textSurface = TTF_RenderText_Blended(font, m_textContent.c_str(), m_colour);
		m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		SDL_FreeSurface(textSurface);

		SDL_QueryTexture(m_texture, NULL, NULL, &m_position.w, &m_position.h);				// Looks at m_texture, extracts the width and height and sets it... pretty smooth. Definitely dodgy.
	}

	void Render(SDL_Renderer*) override {
		SDL_RenderCopy(m_renderer, m_texture, NULL, &m_position);
	}

	void ChangeText(std::string newTextContent) {
		m_textContent = newTextContent;
		PrepareText(m_font);
	}
};

#endif