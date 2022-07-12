#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <string>
#include <map>
#include <iterator>
#include <memory>

#include <semaphore>
#include <thread>

class TextureHandler
{
public:
	static TextureHandler& Instance();
	enum TextureType {
		MenuBackground,
		TileMap,
		Player,
		Projectiles,
		Slime,
		Ghost,
		BigZombie,
		Skeleton,
		Coin,
		Heart
	};
	std::shared_ptr<sf::Texture> getTexture(TextureType type);
	void Initialize();
private:
	void LoadTextures();
	std::map<TextureType, std::shared_ptr<sf::Texture>> textures;
};

