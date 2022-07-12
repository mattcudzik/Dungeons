#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <vector>
#include <memory>

#include "TextureHandler.h"
#include "LevelHandler.h"
#include "Level.h"
#include "HealthComp.h"

class HUD
{
public:
	static const int height = 32;
	void Draw(sf::RenderWindow& window);
	HUD();

	static void UpdateHealthPoints();
	static void UpdateCurrentLevel(int level);
	static void ShowMessage();
	static void HideMessage();
	static bool waitForEnter;
private:
	static sf::Text m_text;
	static sf::Font m_font;
	static std::vector<sf::Sprite> m_hearts;

	static sf::RectangleShape m_messageBackground;
	static sf::Text m_messageTextMain;
	static sf::Text m_messageTextSec;

};

