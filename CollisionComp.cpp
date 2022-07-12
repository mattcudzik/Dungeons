#include "CollisionComp.h"

Component::ComponentType CollisionComp::GetType()
{
	return Component::ComponentType::Collision;
}

CollisionComp::CollisionComp()
{
	collisionTypes.set();
	collisionTypes.set(Level::TileType::floor, 0);
	collisionTypes.set(Level::TileType::spikeFloor, 0);
}

void CollisionComp::SetCollision(Level::TileType type, bool value = true)
{
	this->collisionTypes[type] = value;
}

std::bitset<Level::TileTypeSize>& CollisionComp::GetCollision()
{
	return this->collisionTypes;
}