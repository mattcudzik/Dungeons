#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <memory>
#include <random>

#include "Level.h"
#include "HUD.h"
#include "Assembler.h"


class LevelHandler
{
public:
	static LevelHandler& Instance();
	std::shared_ptr<Level> GetCurrentLevel();
	void Initialize();
	void ChangeNextLevel();
	int currentLevelNumber;
	bool setChange = false;
	void SpawnLadder();
private:
	const int m_levelsAmount = 4;
	std::default_random_engine generator;
	LevelHandler();
	void ChangeLevel(std::string fileName);
	void GenerateQueue();
	void GenerateEnemies();

	std::shared_ptr<Level> currentLevel;
	std::deque<std::string> m_levelQueue;
};

