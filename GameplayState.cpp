#include "GameplayState.h"
#include "RankingHandler.h"
#include "RankingState.h"

GameplayState::GameplayState(sf::Time deltaTime) 
{	
	systems.push_back(std::shared_ptr<InputSystem>(new InputSystem()));
	systems.push_back(std::shared_ptr<EnemySystem>(new EnemySystem()));
	systems.push_back(std::shared_ptr<PhysicsSystem>(new PhysicsSystem(deltaTime)));
	systems.push_back(std::shared_ptr<AnimationSystem>(new AnimationSystem(deltaTime)));
	systems.push_back(std::shared_ptr<ShootSystem>(new ShootSystem()));
	systems.push_back(std::shared_ptr<ProjectileSystem>(new ProjectileSystem()));
	systems.push_back(std::shared_ptr<FlashingSystem>(new FlashingSystem(deltaTime)));
	LevelHandler::Instance().Initialize();
	HUD::UpdateHealthPoints();
}


void GameplayState::Update(sf::Time deltaTime, sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Enter && HUD::waitForEnter)
			{
				HUD::waitForEnter = false;
				HUD::HideMessage();
				EndGameplay();
			}
			if (event.key.code == sf::Keyboard::E && LevelHandler::Instance().GetCurrentLevel()->ladderSpawned)
			{
				if (LevelHandler::Instance().GetCurrentLevel()->IsPlayerCloseToLadder())
				{
					LevelHandler::Instance().setChange = true;
				}
			}
		}
	}
	if (!HUD::waitForEnter)
	{
		LevelHandler::Instance().GetCurrentLevel()->AddEntitiesFromQueue();
		entities = LevelHandler::Instance().GetCurrentLevel()->GetEntities();


		for (auto entity : entities)
		{
			for (auto system : systems)
			{
				system->Update(*entity);
			}
			if (entity->GetToDelete())
			{
				LevelHandler::Instance().GetCurrentLevel()->RemoveEntity(entity->ID);
			}
		}

		if (LevelHandler::Instance().setChange)
		{
			LevelHandler::Instance().ChangeNextLevel();
			LevelHandler::Instance().setChange = false;
		}
		
	}
	
	
}

void GameplayState::Draw(sf::RenderWindow& window) 
{
	entities = LevelHandler::Instance().GetCurrentLevel()->GetEntities();
	LevelHandler::Instance().GetCurrentLevel()->Draw(window);
	for (auto entity : entities)
	{
		entity->Draw(window);
	}
	m_HUD.Draw(window);
}

void GameplayState::EndGameplay()
{
	RankingHandler& rankingHandler = RankingHandler::Instance();
	if (rankingHandler.QualifiedToRanking())
	{
		GameHandler::Instance().AddState(std::shared_ptr<RankingState>(new RankingState(true)));
	}
	else
	{
		rankingHandler.ClearPoints();
		GameHandler::Instance().AddState(std::shared_ptr<MainMenuState>(new MainMenuState()));
	}
	this->toDelete = true;
}