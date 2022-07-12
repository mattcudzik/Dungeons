#pragma once

#include "Component.h"

#include <bitset>
#include "Level.h"

class CollisionComp : public Component
{
private:
	std::bitset<Level::TileTypeSize> collisionTypes;
public:
	ComponentType GetType();
	CollisionComp();
	void SetCollision(Level::TileType type, bool value);
	std::bitset<Level::TileTypeSize>& GetCollision();
};

