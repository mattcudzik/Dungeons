#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Tools.h"
#include "TextureHandler.h"

#include <memory>
#include <vector>

class RankingState : public State
{
public:
	void Update(sf::Time deltaTime, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	RankingState(bool AddPlayer);
private:
	void HideInsertWindow();
	void UpdateRanking();
	void Exit();
	sf::Font m_font;
	std::vector<sf::Text> m_ranking;
	
	sf::Text m_title;
	bool m_insertWindowOpen;
	sf::RectangleShape m_messageBackground;
	sf::Text m_messageTextMain;
	sf::Text m_insertedText;
	sf::Text m_retrunMessage;
	std::string m_insertedString;

};

