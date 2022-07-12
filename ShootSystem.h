#pragma once
#include "System.h"
#include "Entity.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Level.h"
#include "LevelHandler.h"
#include "ShootComp.h"
#include "VelocityComp.h"
#include "Tools.h"

class ShootSystem : public System
{
private:
	std::default_random_engine generator;
	
public:
	ShootSystem();
	void Update(Entity& entity);
};

