#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <memory>

#include "State.h"
#include "Tools.h"
#include "TextureHandler.h"

#include "GameplayState.h"

class MainMenuState : public State
{
public:
	void Update(sf::Time deltaTime, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	MainMenuState();
private:
	void OptionUp();
	void OptionDown();
	void ChooseOption();

	sf::Font m_font;
	sf::Sprite m_background;

	sf::Text m_startGame;
	sf::Text m_exitGame;
	sf::Text m_ranking;

	int m_options = 3;
	int m_chosenOption = 1;
};

