#include "PhysicsSystem.h"

#include "PlayerControlledComp.h"
#include "AccelerationComp.h"
#include "VelocityComp.h"
#include "CollisionComp.h"
#include "HealthComp.h"
#include "CollectableComp.h"
#include "RankingHandler.h"

#include <iostream>
PhysicsSystem::PhysicsSystem(sf::Time deltaTime) :deltaTime(deltaTime) {}

void PhysicsSystem::Update(Entity& entity) {
	if (entity.HasComponent(Component::ComponentType::Velocity))
	{
		std::shared_ptr<VelocityComp> velocityComp = std::dynamic_pointer_cast<VelocityComp>(entity.GetComponent(Component::ComponentType::Velocity));

		if (entity.HasComponent(Component::ComponentType::Acceleration))
		{
			std::shared_ptr<AccelerationComp> accelComp = std::dynamic_pointer_cast<AccelerationComp>(entity.GetComponent(Component::ComponentType::Acceleration));

			sf::Vector2f vel = velocityComp->GetVelocity();
			vel += accelComp->GetAcceleration();

			if (std::abs(vel.x) < 0.02f * Tools::scale)
				vel.x = 0;
			if (std::abs(vel.y) < 0.02f * Tools::scale)
				vel.y = 0;

			velocityComp->SetVelocity(vel);
		}

		if (entity.HasComponent(Component::ComponentType::Collision))
		{
			std::shared_ptr<CollisionComp> collisionComp = std::dynamic_pointer_cast<CollisionComp>(entity.GetComponent(Component::ComponentType::Collision));
			std::bitset<Level::TileTypeSize>& collisionFlags = collisionComp->GetCollision();

			//Move X
			entity.Move(sf::Vector2f(velocityComp->GetVelocity().x * deltaTime.asSeconds(), 0.0f));
			ResolveCollisions(Direction::Horizontal, collisionFlags, entity);

			//Move Y
			entity.Move(sf::Vector2f(0.0f, velocityComp->GetVelocity().y * deltaTime.asSeconds()));
			ResolveCollisions(Direction::Vertical, collisionFlags, entity);
			
		}
		else
		{
			entity.Move(velocityComp->GetVelocity() * deltaTime.asSeconds());
		}
	}
	
	//Collision with player
	std::shared_ptr<Entity> player = LevelHandler::Instance().GetCurrentLevel()->player;
	if (entity.HasComponent(Component::ComponentType::Enemy))
	{
		if (player->hitbox.intersects(entity.hitbox))
		{
			player->SetEntityHealth(-1);
		}
	}
	else if (entity.HasComponent(Component::ComponentType::Collectable))
	{
		std::shared_ptr<CollectableComp> collectableComp = std::dynamic_pointer_cast<CollectableComp>(entity.GetComponent(Component::ComponentType::Collectable));
		if (player->hitbox.intersects(entity.hitbox))
		{
			entity.SetToDelete();
			switch (collectableComp->GetCollectableType())
			{
			case CollectableComp::Type::health:
				player->SetEntityHealth(1);
				break;
			case CollectableComp::Type::points:
				RankingHandler::Instance().AddPoints(10);
				break;
			}
			
		}
	}
}


void PhysicsSystem::ResolveCollisions(Direction direction, std::bitset<Level::TileTypeSize>& collisionFlags, Entity& entity)
{
	sf::FloatRect entityHitbox = entity.hitbox;
	sf::Vector2f entityCenter = { entityHitbox.left + entityHitbox.width / 2.0f, entityHitbox.top + entityHitbox.height / 2.0f };
	std::shared_ptr<Level> currentLevel = LevelHandler::Instance().GetCurrentLevel();

	//Tiles collisions
	float tileSize = Level::tileSize * Tools::scale;


	//TODO add
	//sf::FloatRect mapBounds = sf::FloatRect(0, HUD::height * Tools::scale, tileSize * Level::width, tileSize * Level::height);
	
	
	//OPTIMIZE BY CHECKING ONLY NEARBY TILES
	for (int x = 0; x < Level::width; x++)
		for (int y = 0; y < Level::height; y++)
		{
			Level::TileType tileType = currentLevel->GetTileType(x, y);
			if (collisionFlags[(int)tileType])
			{
				
				sf::FloatRect tileHitbox = sf::FloatRect(x * tileSize, y * tileSize + HUD::height * Tools::scale, tileSize, tileSize);
				sf::Vector2f tileCenter = { tileHitbox.left + tileHitbox.width / 2.0f, tileHitbox.top + tileHitbox.height / 2.0f };
				
				if (entityHitbox.intersects(tileHitbox))
				{
					//Check if projectile and kill on wall collision
					if (entity.HasComponent(Component::ComponentType::Projectile))
					{
						entity.SetToDelete();
					}
					else if (tileType == Level::TileType::spikeFloor)
					{
						entity.SetEntityHealth(-1);
					}
					else
					{
						switch (direction)
						{
						case Direction::Horizontal:
							if (entityCenter.x <= tileCenter.x)
							{
								entity.Move(sf::Vector2f(-(entityHitbox.left + entityHitbox.width - tileHitbox.left), 0.0f));
							}
							else
							{
								entity.Move(sf::Vector2f(tileHitbox.left + tileHitbox.width - entityHitbox.left, 0.0f));
							}
							break;
						case Direction::Vertical:
							if (entityCenter.y <= tileCenter.y)
							{
								entity.Move(sf::Vector2f(0.0f, -(entityHitbox.top + entityHitbox.height - tileHitbox.top)));
							}
							else
							{
								entity.Move(sf::Vector2f(0.0f, tileHitbox.top + tileHitbox.height - entityHitbox.top));
							}
							break;
						}

						entityHitbox = entity.hitbox;
					}
				}
				
			}
		}

}

