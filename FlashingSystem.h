#pragma once
#include <memory>

#include "System.h"

#include "HealthComp.h"
#include "SpriteComp.h"

class FlashingSystem : public System
{
private:
	const sf::Time deltaTime;
public:
	FlashingSystem(sf::Time deltaTime);
	void Update(Entity& entity);
};

