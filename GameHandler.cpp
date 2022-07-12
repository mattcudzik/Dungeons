#include "GameHandler.h"
sf::Vector2i GameHandler::windowSize = sf::Vector2i();
GameHandler::GameHandler() :timeStep(sf::seconds(1.0f / 60.0f)) {}

sf::Time GameHandler::GetTimeStep() {
    return timeStep;
}

GameHandler& GameHandler::Instance() 
{
	static GameHandler instance;
	return instance;
}

void GameHandler::Initialize() 
{
    TextureHandler::Instance().Initialize();
    LevelHandler::Instance().Initialize();
    RankingHandler::Instance().Initialize();

    float scale = Tools::scale;
    
    windowSize = sf::Vector2i(Level::width * Level::tileSize * scale, (Level::height * Level::tileSize + HUD::height) * scale);
	window.create(sf::VideoMode(windowSize.x,windowSize.y), "Mateusz Cudzik PK4 Projekt");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    std::shared_ptr<MainMenuState> menuState(new MainMenuState());
    states.push_back(move(menuState));
}

void GameHandler::GameLoop() 
{
    while (window.isOpen())
    {
        elapsedTime += clock.restart();

        auto stateIt = states.begin();
        while (stateIt != states.end())
        {
            if (stateIt->get()->toDelete)
            {
                stateIt = states.erase(stateIt);
            }
            else
                ++stateIt;
        }

        elapsedTime -= timeStep;
        for (auto& s : states)
        {
            //if(s->IsUpdatable()){}
            s->Update(timeStep, window);
        }

        window.clear();

        for (auto& s : states)
        {
            //if(s->IsDrawable())
                s->Draw(window);
        }

        window.display();
    }
}

void GameHandler::AddState(std::shared_ptr<State> state)
{
    states.push_back(std::move(state));
}