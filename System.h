#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Entity.h"

class System
{
public:
	virtual void Update(Entity& entity) = 0;
};

