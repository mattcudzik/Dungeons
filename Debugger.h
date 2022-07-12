#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Level.h"
#include "LevelHandler.h"
#include "Assembler.h"

//REWORK
class Debugger
{
public:
	static void DebugSpawnSlime(sf::Window& window);
	static void DebugSpawnGhost(sf::Window& window);
	static void DebugSpawnZombie(sf::Window& window);
	static void DebugSpawnSkeleton(sf::Window& window);
	//static void Update();
};

