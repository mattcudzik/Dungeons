#include "Level.h"
#include "HUD.h"

void Level::Load(std::string fileName) {

    std::fstream file;
    file.open(fileName);
    if (file)
    {
        std::string line;
        int i = 0;
        while (std::getline(file, line))
        {
            for (int j = 0; j < line.size(); j++)
            {
                char tile = line[j];
                tileMap[i][j] = (TileType)((int)tile - '0');
            }
            i++;
        }
    }
    // resize the vertex array to fit the level size
    vertArr.setPrimitiveType(sf::Quads);
    vertArr.resize(width * height * 4);
    ReloadLevelTiles();
    
}
void Level::ReloadLevelTiles()
{
    float scale = Tools::scale;
    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tileMap[j][i];

            int tileOffset = 0;

            if (tileNumber == TileType::wall)
            {
                tileOffset = (int)CalculateWallType(j, i);
            }


            // find its position in the tileset texture
            int tu = tileOffset;
            int tv = tileNumber % (tileSet->getSize().x / tileSize);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &vertArr[(j * width + i) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize * scale, (j * tileSize + HUD::height) * scale);
            quad[1].position = sf::Vector2f((i + 1) * tileSize * scale, (j * tileSize + HUD::height) * scale);
            quad[2].position = sf::Vector2f((i + 1) * tileSize * scale, ((j + 1) * tileSize + HUD::height) * scale);
            quad[3].position = sf::Vector2f(i * tileSize * scale, ((j + 1) * tileSize + HUD::height) * scale);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
            quad[3].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);

        }
}
void Level::Draw(sf::RenderWindow& window) {
    window.draw(vertArr, tileSet.get());
}
Level::Level() : enemiesAmount(0), ladderSpawned(false)
{
	tileSet = TextureHandler::Instance().getTexture(TextureHandler::TextureType::TileMap);
	vertArr.setPrimitiveType(sf::PrimitiveType::Quads);
    
}
Level::TileType Level::GetTileType(int x, int y)
{
    return tileMap[y][x];
}
std::vector<std::shared_ptr<Entity>>& Level::GetEntities()
{
    return m_entities;
}
void Level::AddEntity(Entity entity)
{
    m_entitiesToAdd.push(std::make_shared<Entity>(entity));
    if (entity.HasComponent(Component::ComponentType::Enemy))
        this->enemiesAmount++;
}
void Level::AddEntity(std::shared_ptr<Entity> entity)
{
    m_entitiesToAdd.push(entity);
}
void Level::RemoveEntity(size_t ID)
{
    auto entityIt = m_entities.begin();
    while (entityIt != m_entities.end())
    {
        if (entityIt->get()->ID == ID)
        {
            m_entities.erase(entityIt);
            return;
        }
        else
            ++entityIt;
    }
}
void Level::AddEntitiesFromQueue()
{
    std::shared_ptr<Entity> tmp;
    bool added;

    for (int i = 0; i < m_entitiesToAdd.size(); i++)
    {
        tmp = m_entitiesToAdd.front();
        added = false;

        auto entityIt = m_entities.begin();
        while (entityIt != m_entities.end())
        {
            if (entityIt->get()->GetLayer() > tmp->GetLayer())
            {
                m_entities.insert(entityIt, tmp);
                added = true;
                break;
            }
            ++entityIt;
        }
        if (!added)
        {
            m_entities.push_back(tmp);
        }

        m_entitiesToAdd.pop();
    }
}
Level::WallType Level::CalculateWallType(int i, int j)
{
    //Get neighbours
    int topN;
    int botN;
    int leftN;
    int rightN;

    //TOP
    if (i <= 0)
        topN = -1;
    else
        topN = tileMap[i - 1][j];

    //BOT
    if (i >= this->height - 1)
        botN = -1;
    else
        botN = tileMap[i + 1][j];
    
    //LEFT
    if (j <= 0)
        leftN = -1;
    else
        leftN = tileMap[i][j - 1];

    //RIGHT
    if (j >= this->width - 1)
        rightN = -1;
    else
        rightN = tileMap[i][j + 1];

    //RULES
    //4 sides
    if (botN == 1 && topN == 1 && leftN == 1 && rightN == 1)
        return WallType::all_sides;
    //3 sides
    else if (botN != 1 && topN == 1 && leftN == 1 && rightN == 1)
        return WallType::T_top;
    else if (botN == 1 && topN != 1 && leftN == 1 && rightN == 1)
        return WallType::T_bot;
    else if (botN == 1 && topN == 1 && leftN == 1 && rightN != 1)
        return WallType::T_left;
    else if (botN == 1 && topN == 1 && leftN != 1 && rightN == 1)
        return WallType::T_right;
    //2 sides
    else if (botN != 1 && topN == 1 && leftN == 1 && rightN != 1)
        return WallType::bot_left_corner;
    else if (botN != 1 && topN == 1 && leftN != 1 && rightN == 1)
        return WallType::bot_right_corner;
    else if (botN == 1 && topN != 1 && leftN == 1 && rightN != 1)
        return WallType::top_left_corner;
    else if (botN == 1 && topN != 1 && leftN != 1 && rightN == 1)
        return WallType::top_right_corner;
    else if (botN != 1 && topN != 1 && leftN == 1 && rightN == 1)
        return WallType::horizontal;
    else if (botN == 1 && topN == 1 && leftN != 1 && rightN != 1)
        return WallType::vertical;
    //1 side
    else if (botN != 1 && topN != 1 && leftN == 1 && rightN != 1)
        return WallType::horizontal_end_right;
    else if (botN != 1 && topN != 1 && leftN != 1 && rightN == 1)
        return WallType::horizontal_end_left;
    else if (botN != 1 && topN == 1 && leftN != 1 && rightN != 1)
        return WallType::vertical_end_bot;
    else if (botN == 1 && topN != 1 && leftN != 1 && rightN != 1)
        return WallType::vertical_end_top;
    //0 sides
    else
        return WallType::no_sides;
}
void Level::AddPlayer()
{
    //TMP create player:
    AddEntity(Assembler::Instance().CreatePlayer(sf::Vector2f(200, 200)));
    AddEntitiesFromQueue();
    player = m_entities.back();
}

void Level::SetTileType(int x, int y, TileType type)
{
    this->tileMap[y][x] = type;
}

bool Level::IsPlayerCloseToLadder()
{
    if (!ladderSpawned)
        return false;
    sf::Vector2f ladderPos;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            if (tileMap[i][j] == TileType::ladder)
            {
                ladderPos = Tools::CalculatePositionOnTile(j, i);
                if (Tools::MagnitudeOfVector(player->position - ladderPos) < tileSize * Tools::scale * 2)
                    return true;
                else
                    return false;
            }

        }
}