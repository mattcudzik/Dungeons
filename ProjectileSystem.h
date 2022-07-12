#pragma once
#include "System.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Level.h"
#include "LevelHandler.h"

#include <ranges>
class ProjectileSystem : public System
{
public:
	void Update(Entity& entity);
};

