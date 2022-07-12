#include "RankingState.h"
#include "GameHandler.h"
#include <string>
#include <regex>

RankingState::RankingState(bool AddPlayer) : m_insertWindowOpen(AddPlayer)
{
	float scale = Tools::scale;
	m_font.loadFromFile("Textures/PixeloidSans.ttf");

	m_title.setFont(m_font);
	m_title.setCharacterSize(32 * scale);
	m_title.setString("Ranking");
	m_title.setOrigin(sf::Vector2f(m_title.getGlobalBounds().width / 2, 0));
	m_title.setPosition(sf::Vector2f(GameHandler::windowSize.y / 2, 16 * scale));

	m_retrunMessage.setFont(m_font);
	m_retrunMessage.setCharacterSize(14 * scale);
	m_retrunMessage.setString("Press ESC to return");
	m_retrunMessage.setPosition(sf::Vector2f(16 * 9 * scale, 16 * 14.5f * scale));

	UpdateRanking();
	if (AddPlayer)
	{
		m_messageBackground.setFillColor(sf::Color(0, 0, 0, 200));
		m_messageBackground.setPosition(sf::Vector2f(16 * 4 * scale, 4 * 16 * scale));
		m_messageBackground.setSize(sf::Vector2f(16 * 12 * scale, 16 * 8 * scale));

		m_messageTextMain.setFont(m_font);
		m_messageTextMain.setString("Insert your name:");
		m_messageTextMain.setFillColor(sf::Color::White);
		m_messageTextMain.setCharacterSize(24 * scale);
		m_messageTextMain.setPosition(m_messageBackground.getPosition() - sf::Vector2f(m_messageTextMain.getGlobalBounds().width / 2, 0) + sf::Vector2f(m_messageBackground.getGlobalBounds().width / 2, 16 * scale));

		m_insertedText.setFont(m_font);
		m_insertedText.setCharacterSize(24 * scale);
		m_insertedText.setPosition(m_messageBackground.getPosition() - sf::Vector2f(m_messageTextMain.getGlobalBounds().width / 2, 0) + sf::Vector2f(m_messageBackground.getGlobalBounds().width / 2, 16 * 3 * scale));

	}
}
void RankingState::Update(sf::Time deltaTime, sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Exit();
			}
		}
		if (m_insertWindowOpen)
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (m_insertedString.size() < 10)
				{
					std::string sign;
					sign.push_back((char)event.text.unicode);
					std::regex letters("([a-zA-Z]{1})");
					if (std::regex_match(sign, letters))
					{
						m_insertedString += sign;
						m_insertedText.setString(m_insertedString);
					}

				}
				if (event.text.unicode == 8)
				{
					if (m_insertedString.size() != 0)
					{
						m_insertedString.pop_back();
						m_insertedText.setString(m_insertedString);
					}
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Enter && m_insertedString.size() > 2)
				{
					m_insertWindowOpen = false;
					HideInsertWindow();
					RankingHandler::Instance().AddToRanking(m_insertedString);
					UpdateRanking();
				}
			}
		}
		
	}
}

void RankingState::Draw(sf::RenderWindow& window)
{
	window.draw(m_title);
	window.draw(m_retrunMessage);
	for (auto& el : m_ranking)
		window.draw(el);
	window.draw(m_messageBackground);
	window.draw(m_messageTextMain);
	window.draw(m_insertedText);
}
void RankingState::HideInsertWindow()
{
	m_insertedText.setCharacterSize(0);
	m_messageBackground.setSize(sf::Vector2f(0.f, 0.f));
	m_messageTextMain.setCharacterSize(0);

}
void RankingState::UpdateRanking()
{
	m_ranking.clear();
	float scale = Tools::scale;
	auto& ranking = RankingHandler::Instance().GetRanking();
	for (int i = 0; i < ranking.size(); i++)
	{
		sf::Text tmpText = sf::Text();
		tmpText.setCharacterSize(16 * scale);
		tmpText.setFont(m_font);
		tmpText.setPosition(sf::Vector2f(16 * 4 * scale, 16 * (4 + i) * scale));
		tmpText.setString(std::to_string(i + 1) + ". " + ranking[i].first + "\t" + std::to_string(ranking[i].second));
		m_ranking.emplace_back(tmpText);
	}
}
void RankingState::Exit()
{
	GameHandler::Instance().AddState(std::shared_ptr<MainMenuState>(new MainMenuState()));
	this->toDelete = true;
}