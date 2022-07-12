#pragma once
#include "Component.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

class VelocityComp : public Component
{
public:
	ComponentType GetType();
	sf::Vector2f GetDirection();
	sf::Vector2f GetVelocity();
	void SetDirection(sf::Vector2f direction);
	void SetVelocity(sf::Vector2f velocity);

	VelocityComp();
	VelocityComp(sf::Vector2f iniVelocity, sf::Vector2f iniDir);
private:
	sf::Vector2f velocity;
	sf::Vector2f direction;

};

