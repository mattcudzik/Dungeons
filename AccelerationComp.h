#pragma once
#include "Component.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"


class AccelerationComp : public Component
{
public:
	ComponentType GetType();
	sf::Vector2f GetAcceleration();
	void SetAcceleration(sf::Vector2f acceleration);
	AccelerationComp();
private:
	sf::Vector2f acceleration;
};

