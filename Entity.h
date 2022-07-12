#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <memory>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
#include <bitset>

#include "Tools.h"
#include "TextureHandler.h"

#include "Component.h"


class Entity
{
public:
	void AddComponent(std::shared_ptr<Component> component);
	bool HasComponent(Component::ComponentType type);
	std::shared_ptr<Component> GetComponent(Component::ComponentType type);
	void Move(sf::Vector2f vector);
	int GetLayer();

	Entity(sf::Vector2f position, int layer, sf::Vector2i size);
	void Draw(sf::RenderWindow& window);
	void SetEntityHealth(int amount);
	sf::Vector2f position;
	sf::FloatRect hitbox;
	
	void SetToDelete();
	bool GetToDelete();

	const size_t ID;
	const sf::Vector2i size;
	//TMP Entity name
	std::string name;
private:
	void OnDeath();
	std::bitset<Component::TypesAmount> componentFlags;
	std::vector<std::shared_ptr<Component>> components;
	bool toDelete;
	int m_layer;

	static size_t IDcounter()
	{
		static size_t IDcounter = 0;
		return IDcounter++;
	}
};
