#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

class State
{
public:
	virtual void Update(sf::Time deltaTime, sf::RenderWindow& window) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	State();

	bool IsDrawable();
	bool IsUpdatable();
	void SetDrawable(bool cond);
	void SetUpdatable(bool cond);

	bool toDelete = false;
protected:
	bool updatable;
	bool drawable;
};

