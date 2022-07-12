#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Entity.h"
#include "TextureHandler.h"
#include "ProjectileComp.h"

#include <cmath>
#include <bitset>

class Assembler 
{
public:
	static Assembler& Instance();

	Entity CreatePlayer(sf::Vector2f position);
	Entity CreateProjectile(sf::Vector2f position, sf::Vector2f direction, ProjectileComp::Target target, ProjectileComp::Type type, float speed);
	Entity CreateSlime(sf::Vector2f position);
	Entity CreateGhost(sf::Vector2f position);
	Entity CreateBigZombie(sf::Vector2f position);
	Entity CreateSkeleton(sf::Vector2f position);
	Entity CreateCoin(sf::Vector2f position);
private:
	Assembler();
};

