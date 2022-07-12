#pragma once
#include <iostream>


#include <iostream>
#include <memory>
#include <fstream>
#include <iterator>

#include "State.h"
#include "GameplayState.h"
#include "MainMenuState.h"
#include "TextureHandler.h"
#include "RankingHandler.h"
#include "Tools.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

class GameHandler
{
public:
	void Initialize();
	void GameLoop();
	void AddState(std::shared_ptr<State> state);
	static GameHandler& Instance();
	sf::Time GetTimeStep();
	static sf::Vector2i windowSize;
	sf::RenderWindow window;
private:
	GameHandler();
	std::vector<std::shared_ptr<State>> states;

	sf::Clock clock;
	sf::Time elapsedTime;
	const sf::Time timeStep;
};

