#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Entity.h"
#include "System.h"


//TODO: REWORK
class AnimationSystem : public System
{
private:
	const sf::Time deltaTime;
public:
	void Update(Entity& entity);
	AnimationSystem(sf::Time deltaTime);
};

