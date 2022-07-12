#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"



class Tools
{
public:
	static Tools& Instance();
	const static float scale;
	static sf::Vector2f NormalizeVector(sf::Vector2f vector);
	static float MagnitudeOfVector(sf::Vector2f vector);
	static sf::Vector2f CalculatePositionOnTile(int x, int y);
private:
	Tools();
};

