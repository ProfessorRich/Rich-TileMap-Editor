#pragma once

#include <SDL.h>
#include <string>

#include "TextureManager.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "Animation.h"

class SpriteComponent : public Component {
private:
	TransformComponent* m_transform;
	SDL_Texture* m_texture;
	SDL_Rect m_sourceRectangle;						// the rectangle in the m_texture which contains the current sprite to be drawn
	SDL_Rect m_destinationRectangle;				// the rectangle where the current sprite will be drawn on the screen
	glm::vec2 m_tileIndex;
	int m_tileSize;
	bool m_isFixed;

	bool m_isAnimated;
	unsigned int m_numFrames;
	unsigned int m_animationSpeed;
	std::map<std::string, Animation> m_animations;
	std::string m_currentAnimationName;
	unsigned int m_animationIndex = 0;

public:

	SpriteComponent(std::string assetTextureId, int tileSize, int sourceRow, int sourceColumn) {
		m_isFixed = false;
		SetTexture(assetTextureId);
		m_tileSize = tileSize;
		m_tileIndex.x = sourceColumn;
		m_tileIndex.y = sourceRow;
	}

	SpriteComponent(std::string assetTextureId, int tileSize, int row, int column, bool isFixed) {
		m_isFixed = isFixed;
		SetTexture(assetTextureId);
		m_tileSize = tileSize;
		m_tileIndex.x = column;
		m_tileIndex.y = row;
	}

	SpriteComponent(std::string assetTextureId, int tileSize, int row, int column, bool isFixed, bool isAnimated, int numFrames) {
		m_isFixed = isFixed;
		SetTexture(assetTextureId);
		m_tileSize = tileSize;
		m_tileIndex.x = column;
		m_tileIndex.y = row;

		m_isAnimated = isAnimated;
		m_numFrames = numFrames;
		m_animationSpeed = 2;

		Animation singleDirectionAnimation = Animation(0, m_numFrames, m_animationSpeed);
		m_animations.emplace("SingleAnimation", singleDirectionAnimation);
		m_animationIndex = 0;
		m_currentAnimationName = "SingleAnimation";

		Play(m_currentAnimationName);

	}

	void Play(std::string animationName) {
		m_numFrames = m_animations.at(animationName).g_numFrames;
		m_animationIndex = m_animations.at(animationName).g_index;
		m_animationSpeed = m_animations.at(animationName).g_animationSpeed;

		m_currentAnimationName = animationName;
	}

	void SetTexture(std::string assetTextureId) {
		m_texture = Editor::g_assetManager->GetTexture(assetTextureId);
	}

	void Initialise() override {
		m_transform = g_owner->GetComponent<TransformComponent>();
		m_sourceRectangle.x = m_tileSize * m_tileIndex.x;
		m_sourceRectangle.y = m_tileSize * m_tileIndex.y;
		m_sourceRectangle.w = m_transform->g_width;
		m_sourceRectangle.h = m_transform->g_height;
	}

	void Update(float deltaTime) override {
		if (m_isAnimated) {
			// Clamp that baitch to 10
			if (m_animationSpeed > 10) {
				m_animationSpeed = 10;
			}

			// Superl33t formula to ensure m_animationSpeed 1 - 10 provides number from 1000 to 50 which translates to speed which m_numFrames cycles. All my own work.
			m_sourceRectangle.x = (m_sourceRectangle.w * (static_cast<int>(SDL_GetTicks() / (1000 - ((1000 - 50) / 9) * (m_animationSpeed - 1))) % m_numFrames));
		}
		m_sourceRectangle.y = m_animationIndex * m_transform->g_height;

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
