#pragma once
#include "SFML/System.hpp"

#include "System.h"
#include "Level.h"
#include "LevelHandler.h"
#include "Tools.h"

#include <ctime>
#include <random>

class EnemySystem : public System
{
public:
	void Update(Entity& entity);
};

