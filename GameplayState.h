#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "State.h"
#include "Level.h"
#include "System.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "AnimationSystem.h"
#include "ShootSystem.h"
#include "FlashingSystem.h"
#include "EnemySystem.h"
#include "ProjectileSystem.h"

#include "Entity.h"
#include "LevelHandler.h"
#include "HUD.h"
#include "GameHandler.h"

#include <vector>

class GameplayState : public State
{
public:

	void Update(sf::Time deltaTime, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	GameplayState(sf::Time deltaTime);

private:
	void EndGameplay();
	HUD m_HUD;
	std::vector<std::shared_ptr<System>> systems;
	std::vector<std::shared_ptr<Entity>> entities;
};

