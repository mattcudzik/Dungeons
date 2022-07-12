#include "LevelHandler.h"

LevelHandler::LevelHandler()
{
	currentLevelNumber = 1;
}

LevelHandler& LevelHandler::Instance()
{
	static LevelHandler instance;
	return instance;
}

void LevelHandler::Initialize()
{
	currentLevelNumber = 1;
	setChange = false;
	currentLevel = nullptr;
	m_levelQueue.clear();

	std::random_device r;
	generator = std::default_random_engine(r());
	GenerateQueue();
	currentLevel = std::make_shared<Level>();
	currentLevel->Load(m_levelQueue.front());
	m_levelQueue.pop_front();
	currentLevel->AddPlayer();
	GenerateEnemies();
}

std::shared_ptr<Level> LevelHandler::GetCurrentLevel()
{
	return this->currentLevel;
}

void LevelHandler::ChangeLevel(std::string fileName)
{

	std::shared_ptr<Level> nextLevel = std::shared_ptr<Level>(new Level());
	nextLevel->Load(fileName);
	nextLevel->player = currentLevel->player;
	nextLevel->AddEntity(nextLevel->player);
	nextLevel->AddEntitiesFromQueue();
	currentLevel = nextLevel;
	
	GenerateEnemies();
}

void LevelHandler::GenerateQueue()
{
	std::uniform_int_distribution<int> distirbution(1, m_levelsAmount);
	for (int i = 0; i < 10; i++)
	{
		std::string fileName = "Levels/" + std::to_string(distirbution(generator)) + ".txt";
		if (!m_levelQueue.empty())
		{
			while (m_levelQueue.back() == fileName)
				fileName = "Levels/" + std::to_string(distirbution(generator)) + ".txt";
		}
		this->m_levelQueue.push_back(fileName);
	}
}

void LevelHandler::ChangeNextLevel()
{
	if (m_levelQueue.empty())
	{
		GenerateQueue();
	}
	ChangeLevel(m_levelQueue.front());
	m_levelQueue.pop_front();
	currentLevelNumber++;
	HUD::UpdateCurrentLevel(currentLevelNumber);
}

void LevelHandler::GenerateEnemies()
{
	std::normal_distribution<> normalDistribution(5, 2);
	int amountOfEnemies = std::round(normalDistribution(generator));
	if (amountOfEnemies < 0)
		amountOfEnemies = 1;
	else if (amountOfEnemies > 10)
		amountOfEnemies = 10;
	sf::Vector2f playerPosition = currentLevel->player->position;
	std::uniform_int_distribution<int> xDistirbution(1,Level::width-1);
	std::uniform_int_distribution<int> yDistirbution(1,Level::height-1);

	for (int i = 0; i < amountOfEnemies; i++)
	{
		sf::Vector2i mapPosition = sf::Vector2i(xDistirbution(generator), yDistirbution(generator));
		bool correctPosition = true;

		do
		{
			Level::TileType tileType = currentLevel->GetTileType(mapPosition.x, mapPosition.y);
			if (tileType == Level::TileType::wall || tileType == Level::TileType::hole || Tools::MagnitudeOfVector(Tools::CalculatePositionOnTile(mapPosition.x, mapPosition.y) - playerPosition) < 16 * 5 * Tools::scale)
			{
				mapPosition = sf::Vector2i(xDistirbution(generator), yDistirbution(generator));
			}
			else
				correctPosition = false;
		} while (correctPosition);

		sf::Vector2f position = Tools::CalculatePositionOnTile(mapPosition.x, mapPosition.y);

		std::uniform_int_distribution<int> enemyDistirbution(1, 8);
		int enemy = enemyDistirbution(generator);
		switch (enemy)
		{
		case 1:
			currentLevel->AddEntity(Assembler::Instance().CreateBigZombie(position));
			break;
		case 2:
		case 5:
		case 8:
			currentLevel->AddEntity(Assembler::Instance().CreateGhost(position));
			break;
		case 3:
		case 7:
			currentLevel->AddEntity(Assembler::Instance().CreateSkeleton(position));
			break;
		case 4:
		case 6:
			currentLevel->AddEntity(Assembler::Instance().CreateSlime(position));
			break;
		}
	}

}

void LevelHandler::SpawnLadder()
{
	std::uniform_int_distribution<int> xDistirbution(1, Level::width - 1);
	std::uniform_int_distribution<int> yDistirbution(1, Level::height - 1);

	sf::Vector2i mapPosition = sf::Vector2i(xDistirbution(generator), yDistirbution(generator));
	bool correctPosition = true;
	do
	{
		Level::TileType tileType = currentLevel->GetTileType(mapPosition.x, mapPosition.y);
		if (tileType == Level::TileType::wall || tileType == Level::TileType::spikeFloor)
		{
			mapPosition = sf::Vector2i(xDistirbution(generator), yDistirbution(generator));
		}
		else
			correctPosition = false;
	} while (correctPosition);

	currentLevel->SetTileType(mapPosition.x, mapPosition.y, Level::TileType::ladder);
	currentLevel->ladderSpawned = true;
	currentLevel->ReloadLevelTiles();
}
