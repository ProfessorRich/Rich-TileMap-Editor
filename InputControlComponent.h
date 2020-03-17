#pragma once

#include <SDL.h>
#include <iostream>
#include <glm.hpp>
#include <string>

#include "EntityManager.h"
#include "Editor.h"
#include "TransformComponent.h"

class InputControlComponent : public Component {
private:
	std::string m_commandReceived;
	std::string m_moveUpKey, m_moveDownKey, m_moveLeftKey, m_moveRightKey;
	TransformComponent* m_transform;

public:
	InputControlComponent() {
		m_moveUpKey = GetSDLKeyStringCode("up");
		m_moveRightKey = GetSDLKeyStringCode("right");
		m_moveDownKey = GetSDLKeyStringCode("down");
		m_moveLeftKey = GetSDLKeyStringCode("left");
	}

	void Initialise() {
		m_transform = g_owner->GetComponent<TransformComponent>();
	}

	// Converts string description of key to SDL key codes
	std::string GetSDLKeyStringCode(std::string key) {
		if (key.compare("up") == 0) return "119";
		if (key.compare("right") == 0) return "100";
		if (key.compare("down") == 0) return "115";
		if (key.compare("left") == 0) return "97";
		return std::to_string(static_cast<int>(key[0]));  // if it's none of the above then return the standard ASCII mapping and hope for the best...
	}

	void ProcessInput(std::string keyCode) {
	
		if (keyCode.compare(m_moveUpKey) == 0) {
			m_commandReceived = "up";
		}

		if (keyCode.compare(m_moveDownKey) == 0) {
			m_commandReceived = "down";
		}
		
		if (keyCode.compare(m_moveLeftKey) == 0) {
			m_commandReceived = "left";
		}
		
		if (keyCode.compare(m_moveRightKey) == 0) {
			m_commandReceived = "right";
		}
	}

	void Update(float deltaTime) {
		// if nuffin, return now bruh.
		if (m_commandReceived.empty()) {
			return;
		}
		else if (m_commandReceived.compare("up") == 0) {
			m_transform->g_position.y -= 32;
		}
		else if (m_commandReceived.compare("right") == 0) {
			m_transform->g_position.x += 32;
		}
		else if (m_commandReceived.compare("down") == 0) {
			m_transform->g_position.y += 32;
		}
		else if (m_commandReceived.compare("left") == 0) {
			m_transform->g_position.x -= 32;
		}

		// clear that baitch so we're ready for the next command, bruh.
		m_commandReceived.clear();
	}


	void Render() {
	}

};
