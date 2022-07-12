#include "TextureHandler.h"

#include <iostream>

std::counting_semaphore partA{ 1 }, partB{ 1 }, partC{ 1 }, access{ 1 };
TextureHandler& TextureHandler::Instance() 
{
	static TextureHandler instance;
	return instance;
}
void TextureHandler::Initialize()
{
	/*std::shared_ptr<sf::Texture> tmp;

	tmp = std::make_shared<sf::Texture>();
	tmp->loadFromFile("Textures/menuBackground.png");
	tmp->setSmooth(false);
	textures[MenuBackground] = tmp;

	tmp = std::make_shared<sf::Texture>();
	tmp->loadFromFile("Textures/tiles.png");
	textures[TileMap] = tmp;

	tmp = std::make_shared<sf::Texture>();
	tmp->loadFromFile("Textures/player.png");
	textures[Player] = tmp;

	tmp = std::make_shared<sf::Texture>();
	tmp->loadFromFile("Textures/zombie.png");
	textures[BigZombie] = tmp;

	tmp = std::make_shared<sf::Texture>();
	tmp->loadFromFile("Textures/projectile.png");
	tmp->setSmooth(false);
	textures[Projectiles] = tmp;

	tmp = std::make_shared<sf::Texture>();
	tmp->loadFromFile("Textures/slime.png");
	tmp->setSmooth(false);
	textures[Slime] = tmp;

	tmp = std::make_shared<sf::Texture>();
	tmp->loadFromFile("Textures/ghost.png");
	tmp->setSmooth(false);
	textures[Ghost] = tmp;

	tmp = std::make_shared<sf::Texture>();
	tmp->loadFromFile("Textures/skeleton.png");
	tmp->setSmooth(false);
	textures[Skeleton] = tmp;

	tmp = std::make_shared<sf::Texture>();
	tmp->loadFromFile("Textures/coin.png");
	tmp->setSmooth(false);
	textures[Coin] = tmp;

	tmp = std::make_shared<sf::Texture>();
	tmp->loadFromFile("Textures/heart.png");
	tmp->setSmooth(false);
	textures[Heart] = tmp;*/

	std::thread t1(&TextureHandler::LoadTextures, *this);
	std::thread t2(&TextureHandler::LoadTextures, *this);
	std::thread t3(&TextureHandler::LoadTextures, *this);

	t1.join();
	t2.join();
	t3.join();
}

void TextureHandler::LoadTextures()
{
	std::shared_ptr<sf::Texture> tmp;
	TextureHandler& test = TextureHandler::Instance();
	if (partA.try_acquire())
	{
		tmp = std::make_shared<sf::Texture>();
		tmp->loadFromFile("Textures/menuBackground.png");
		tmp->setSmooth(false);
		access.acquire();
		test.textures[MenuBackground] = tmp;
		access.release();

		tmp = std::make_shared<sf::Texture>();
		tmp->loadFromFile("Textures/tiles.png");
		access.acquire();
		test.textures[TileMap] = tmp;
		access.release();

		tmp = std::make_shared<sf::Texture>();
		tmp->loadFromFile("Textures/player.png");
		access.acquire();
		test.textures[Player] = tmp;
		access.release();

		tmp = std::make_shared<sf::Texture>();
		tmp->loadFromFile("Textures/zombie.png");
		access.acquire();
		test.textures[BigZombie] = tmp;
		access.release();
	}

	else if (partB.try_acquire())
	{
		tmp = std::make_shared<sf::Texture>();
		tmp->loadFromFile("Textures/projectile.png");
		tmp->setSmooth(false);
		access.acquire();
		test.textures[Projectiles] = tmp;
		access.release();

		tmp = std::make_shared<sf::Texture>();
		tmp->loadFromFile("Textures/slime.png");
		tmp->setSmooth(false);
		access.acquire();
		test.textures[Slime] = tmp;
		access.release();

		tmp = std::make_shared<sf::Texture>();
		tmp->loadFromFile("Textures/ghost.png");
		tmp->setSmooth(false);
		access.acquire();
		test.textures[Ghost] = tmp;
		access.release();
	}

	else if (partC.try_acquire())
	{
		tmp = std::make_shared<sf::Texture>();
		tmp->loadFromFile("Textures/skeleton.png");
		tmp->setSmooth(false);
		access.acquire();
		test.textures[Skeleton] = tmp;
		access.release();

		tmp = std::make_shared<sf::Texture>();
		tmp->loadFromFile("Textures/coin.png");
		tmp->setSmooth(false);
		access.acquire();
		test.textures[Coin] = tmp;
		access.release();

		tmp = std::make_shared<sf::Texture>();
		tmp->loadFromFile("Textures/heart.png");
		tmp->setSmooth(false);
		access.acquire();
		test.textures[Heart] = tmp;
		access.release();
	}
}

std::shared_ptr<sf::Texture> TextureHandler::getTexture(TextureType type) 
{
	auto textureFound = textures.find(type);
	if (textureFound != textures.end()) 
	{
		return textureFound->second;
	}
	return nullptr;
}
