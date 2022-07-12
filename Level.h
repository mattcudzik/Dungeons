#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <string>

#include "Entity.h"
#include "TextureHandler.h"
#include "Tools.h"
#include "Assembler.h"


#include <memory>
#include <queue>
#include <fstream>

class Level
{
public:
	Level();
	void Load(std::string fileName);
	void Draw(sf::RenderWindow& window);
	void AddEntity(Entity entity);
	void AddEntity(std::shared_ptr<Entity> entity);
	void RemoveEntity(size_t ID);
	void AddEntitiesFromQueue();

	bool ladderSpawned;
	bool IsPlayerCloseToLadder();

	static const int width = 20;
	static const int height = 14;
	static const int tileSize = 16;
	std::shared_ptr<Entity> player;

	enum TileType
	{
		floor = 0,
		wall,
		spikeFloor,
		hole,
		ladder
	};
	static const int TileTypeSize = 5;

	TileType GetTileType(int x, int y);
	void SetTileType(int x, int y, TileType type);
	std::vector<std::shared_ptr<Entity>>& GetEntities();
	int enemiesAmount;

	void AddPlayer();
	void ReloadLevelTiles();
	
private:
	std::shared_ptr<sf::Texture> tileSet;

	std::vector<std::shared_ptr<Entity>> m_entities;
	std::queue<std::shared_ptr<Entity>> m_entitiesToAdd;

	TileType tileMap[height][width];
	sf::VertexArray vertArr;

	enum WallType
	{
		vertical = 0,
		vertical_end_top,
		vertical_end_bot,
		horizontal_end_left,
		horizontal,
		horizontal_end_right,
		top_right_corner,
		top_left_corner,
		bot_right_corner,
		bot_left_corner,
		T_right,
		T_left,
		T_bot,
		T_top,
		all_sides,
		no_sides
	};

	WallType CalculateWallType(int i, int j);
	
};

