#include "MainMenuState.h"
#include "GameHandler.h"
#include "RankingState.h"

MainMenuState::MainMenuState()
{
	float scale = Tools::scale;
	m_background.setTexture(*TextureHandler::Instance().getTexture(TextureHandler::TextureType::MenuBackground));
	m_background.setScale(sf::Vector2f(scale, scale));

	
	float width = 8 * 16 * scale;
	m_font.loadFromFile("Textures/PixeloidSans.ttf");

	m_startGame.setFont(m_font);
	m_startGame.setString("Start");
	m_startGame.setCharacterSize(16 * scale);

	m_startGame.setPosition(sf::Vector2f(6 * 16 * scale + (width - m_startGame.getGlobalBounds().width) / 2, 7 * 16 * scale));
	m_startGame.setStyle(sf::Text::Bold | sf::Text::Underlined);
	

	m_ranking.setFont(m_font);
	m_ranking.setString("Ranking");
	m_ranking.setCharacterSize(16 * scale);
	m_ranking.setFillColor(sf::Color(200, 200, 200));

	m_ranking.setPosition(sf::Vector2f(6 * 16 * scale + (width - m_ranking.getGlobalBounds().width) / 2, 9 * 16 * scale));

	m_exitGame.setFont(m_font);
	m_exitGame.setString("Exit");
	m_exitGame.setCharacterSize(16 * scale);
	m_exitGame.setFillColor(sf::Color(200, 200, 200));

	m_exitGame.setPosition(sf::Vector2f(6 * 16 * scale + (width - m_exitGame.getGlobalBounds().width) / 2, 11 * 16 * scale));
}

void MainMenuState::Update(sf::Time deltaTime, sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::W)
				OptionUp();
			if (event.key.code == sf::Keyboard::S)
				OptionDown();
			if (event.key.code == sf::Keyboard::Enter)
				ChooseOption();
		}
	}
}

void MainMenuState::Draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_startGame);
	window.draw(m_ranking);
	window.draw(m_exitGame);
}

void MainMenuState::OptionUp()
{
	m_chosenOption--;
	if (m_chosenOption < 1)
		m_chosenOption = m_options;

	switch (m_chosenOption)
	{
	case 1:
		m_startGame.setStyle(sf::Text::Bold | sf::Text::Underlined);
		m_startGame.setFillColor(sf::Color::White);

		m_exitGame.setStyle(sf::Text::Regular);
		m_exitGame.setFillColor(sf::Color(200, 200, 200));
		
		m_ranking.setStyle(sf::Text::Regular);
		m_ranking.setFillColor(sf::Color(200, 200, 200));
		break;
	case 3:
		m_exitGame.setStyle(sf::Text::Bold | sf::Text::Underlined);
		m_exitGame.setFillColor(sf::Color::White);

		m_startGame.setStyle(sf::Text::Regular);
		m_startGame.setFillColor(sf::Color(200, 200, 200));

		m_ranking.setStyle(sf::Text::Regular);
		m_ranking.setFillColor(sf::Color(200, 200, 200));
		break;
	case 2:
		m_ranking.setStyle(sf::Text::Bold | sf::Text::Underlined);
		m_ranking.setFillColor(sf::Color::White);

		m_startGame.setStyle(sf::Text::Regular);
		m_startGame.setFillColor(sf::Color(200, 200, 200));

		m_exitGame.setStyle(sf::Text::Regular);
		m_exitGame.setFillColor(sf::Color(200, 200, 200));
		break;
	}
}

void MainMenuState::OptionDown()
{
	m_chosenOption++;
	if (m_chosenOption > m_options)
		m_chosenOption = 1;

	switch (m_chosenOption)
	{
	case 1:
		m_startGame.setStyle(sf::Text::Bold | sf::Text::Underlined);
		m_startGame.setFillColor(sf::Color::White);

		m_exitGame.setStyle(sf::Text::Regular);
		m_exitGame.setFillColor(sf::Color(200, 200, 200));

		m_ranking.setStyle(sf::Text::Regular);
		m_ranking.setFillColor(sf::Color(200, 200, 200));
		break;
	case 3:
		m_exitGame.setStyle(sf::Text::Bold | sf::Text::Underlined);
		m_exitGame.setFillColor(sf::Color::White);

		m_startGame.setStyle(sf::Text::Regular);
		m_startGame.setFillColor(sf::Color(200, 200, 200));

		m_ranking.setStyle(sf::Text::Regular);
		m_ranking.setFillColor(sf::Color(200, 200, 200));
		break;
	case 2:
		m_ranking.setStyle(sf::Text::Bold | sf::Text::Underlined);
		m_ranking.setFillColor(sf::Color::White);

		m_startGame.setStyle(sf::Text::Regular);
		m_startGame.setFillColor(sf::Color(200, 200, 200));

		m_exitGame.setStyle(sf::Text::Regular);
		m_exitGame.setFillColor(sf::Color(200, 200, 200));
		break;
	}
}

void MainMenuState::ChooseOption()
{
	switch (m_chosenOption)
	{
	case 1:
		GameHandler::Instance().AddState(std::shared_ptr<GameplayState>(new GameplayState(GameHandler::Instance().GetTimeStep())));
		this->toDelete = true;
		break;
	case 2:
		GameHandler::Instance().AddState(std::shared_ptr<RankingState>(new RankingState(false)));
		this->toDelete = true;
		break;
	case 3:
		GameHandler::Instance().window.close();
		break;
	}
}