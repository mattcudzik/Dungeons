#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Animation
{
public:
	Animation(int animNumber, sf::Vector2i size);
	sf::IntRect& GetNextFrame();
	const float frameTime;
	void ResetAnimation();
private:
	int currentFrame;
	std::vector<sf::IntRect> frames;
};

