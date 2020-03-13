#pragma once

#include <SDL.h>
#include <string>

#include "TextureManager.h"
#include "AssetManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
private:
	TransformComponent* m_transform;
	SDL_Texture* m_texture;
	SDL_Rect m_sourceRectangle;						// the rectangle in the m_texture which contains the current sprite to be drawn
	SDL_Rect m_destinationRectangle;				// the rectangle where the current sprite will be drawn on the screen
	bool m_isFixed;

public:

	SpriteComponent(std::string assetTextureId) {
		m_isFixed = false;
		SetTexture(assetTextureId);
	}

	SpriteComponent(std::string assetTextureId, bool isFixed) {
		m_isFixed = isFixed;
		SetTexture(assetTextureId);
	}

	void SetTexture(std::string assetTextureId) {
		m_texture = 
			Editor::g_assetManager->GetTexture(assetTextureId);
	}

	void Initialise() override {
		m_transform = g_owner->GetComponent<TransformComponent>();
		m_sourceRectangle.x = 0;
		m_sourceRectangle.y = 0;
		m_sourceRectangle.w = m_transform->g_width;
		m_sourceRectangle.h = m_transform->g_height;
	}

	void Update(float deltaTime) override {
		m_sourceRectangle.y = 0; // TODO - Multiplate rows

		// If m_isFixed (GUI elements etc) then don't adjust for camera.
		if (m_isFixed) {
			m_destinationRectangle.x = static_cast<int>(m_transform->g_position.x);
			m_destinationRectangle.y = static_cast<int>(m_transform->g_position.y);
		}
		else {
			m_destinationRectangle.x = static_cast<int>(m_transform->g_position.x) - Editor::g_camera.x;
			m_destinationRectangle.y = static_cast<int>(m_transform->g_position.y) - Editor::g_camera.y;
		}

		m_destinationRectangle.w = m_transform->g_width * m_transform->g_scale;
		m_destinationRectangle.h = m_transform->g_height * m_transform->g_scale;
	}

	void Render(SDL_Renderer* theRenderer) override {
		TextureManager::Draw(m_texture, m_sourceRectangle, m_destinationRectangle, theRenderer);
	}


};
