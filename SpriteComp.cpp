#include "SpriteComp.h"

#define DEF_SIZE 16
SpriteComp::SpriteComp(TextureHandler::TextureType textureType, sf::Vector2f position)
{
	this->m_textureType = textureType;
	this->flipped = false;
	this->m_sprite.setTexture(*(TextureHandler::Instance().getTexture(textureType).get()));
	this->m_sprite.setTextureRect(sf::IntRect(0, 0, DEF_SIZE, DEF_SIZE));
	float scale = Tools::Instance().scale;
	this->m_sprite.setScale(sf::Vector2f(scale, scale));
	this->m_sprite.setPosition(position);
}
SpriteComp::SpriteComp(TextureHandler::TextureType textureType, sf::IntRect spriteRect, sf::Vector2f position)
{
	this->m_textureType = textureType;
	this->flipped = false;
	this->m_sprite.setTexture(*(TextureHandler::Instance().getTexture(textureType).get()));
	this->m_sprite.setTextureRect(spriteRect);
	float scale = Tools::Instance().scale;
	this->m_sprite.setScale(sf::Vector2f(scale, scale));
	this->m_sprite.setPosition(position);
}

Component::ComponentType SpriteComp::GetType()
{
	return Component::ComponentType::Sprite;
}

sf::Sprite& SpriteComp::GetSprite()
{
	return this->m_sprite;
}

void SpriteComp::SetSprite(sf::IntRect rect)
{
	this->m_sprite.setTextureRect(rect);
}

void SpriteComp::FlipXSprite(bool arg)
{
	sf::Vector2f currentScale = m_sprite.getScale();
	// flip X
	if (!flipped && arg)
	{
		m_sprite.setScale(sf::Vector2f(-currentScale.x, currentScale.y));
		m_sprite.move(sf::Vector2f(m_sprite.getGlobalBounds().width, 0.f));
		flipped = true;
	}
	// unflip X
	else if (flipped && !arg)
	{
		m_sprite.setScale(sf::Vector2f(-currentScale.x, currentScale.y));
		m_sprite.move(sf::Vector2f(-m_sprite.getGlobalBounds().width, 0.f));
		flipped = false;
	}
}

TextureHandler::TextureType SpriteComp::GetTextureType()
{
	return this->m_textureType;
}