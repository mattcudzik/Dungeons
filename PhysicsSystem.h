#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <bitset>

#include "System.h"
#include "Level.h"
#include "Tools.h"
#include "LevelHandler.h"
#include "HUD.h"


class PhysicsSystem : public System
{
private:
	const sf::Time deltaTime;
	enum Direction
	{
		Horizontal,
		Vertical
	};
	void ResolveCollisions(Direction direction, std::bitset<Level::TileTypeSize>& collisionFlags, Entity& entity);
public:
	PhysicsSystem(sf::Time deltaTime);
	void Update(Entity& entity);
};