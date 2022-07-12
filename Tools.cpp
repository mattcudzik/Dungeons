#include "Tools.h"
#include "HUD.h"
const float Tools::scale = 3.5f;
Tools::Tools() {}

Tools& Tools::Instance() 
{
	static Tools instance;
	return instance;
}

sf::Vector2f Tools::NormalizeVector(sf::Vector2f vector)
{
	float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	if (magnitude != 0)
		vector /= magnitude;
	return vector;
}

float Tools::MagnitudeOfVector(sf::Vector2f vector)
{
	return std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

sf::Vector2f Tools::CalculatePositionOnTile(int x, int y)
{
	sf::Vector2f position;
	position.y = HUD::height * scale + y * Level::tileSize * scale;
	position.x = x * Level::tileSize * scale;
	return position;
}
