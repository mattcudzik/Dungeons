#pragma once
#include <memory>

#include "Component.h"

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "TextureHandler.h"
#include "Tools.h"

class SpriteComp : public Component
{
public:
	ComponentType GetType();
	sf::Sprite& GetSprite();
	SpriteComp(TextureHandler::TextureType textureType, sf::Vector2f position);
	SpriteComp(TextureHandler::TextureType textureType, sf::IntRect spriteRect, sf::Vector2f position);
	void SetSprite(sf::IntRect rect);
	void FlipXSprite(bool arg);

	TextureHandler::TextureType GetTextureType();
private:
	sf::Sprite m_sprite;
	bool flipped;
	TextureHandler::TextureType m_textureType;
};

