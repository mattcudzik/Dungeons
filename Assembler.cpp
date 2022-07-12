#include "Assembler.h"

#include "PlayerControlledComp.h"
#include "AccelerationComp.h"
#include "VelocityComp.h"
#include "SpriteComp.h"
#include "CollisionComp.h"
#include "AnimationComp.h"
#include "ShootComp.h"
#include "HealthComp.h"
#include "ProjectileComp.h"
#include "EnemyComp.h"
#include "StaticAnimationComp.h"
#include "CollectableComp.h"

#define M_PI 3.14159265358979323846
Assembler::Assembler() {};

/*
Layers:
0-background
10-entities
20-flying enities
40-player
50-projectiles
*/

Assembler& Assembler::Instance()
{
	static Assembler instance;
	return instance;
}

Entity Assembler::CreatePlayer(sf::Vector2f position)
{
	Entity entity(position, 40, sf::Vector2i(16, 32));
	float scale = Tools::scale;
	

	entity.AddComponent(std::shared_ptr<AccelerationComp>(new AccelerationComp()));
	entity.AddComponent(std::shared_ptr<VelocityComp>(new VelocityComp()));
	entity.AddComponent(std::shared_ptr<PlayerControlledComp>(new PlayerControlledComp(70.f * scale, 0.05f * scale)));
	entity.AddComponent(std::shared_ptr<SpriteComp>(new SpriteComp(TextureHandler::TextureType::Player, position)));

	std::shared_ptr<CollisionComp> collisionComp = std::shared_ptr<CollisionComp>(new CollisionComp());
	collisionComp->SetCollision(Level::TileType::spikeFloor, true);
	entity.AddComponent(collisionComp);

	entity.AddComponent(std::shared_ptr<AnimationComp>(new AnimationComp(entity.size, std::bitset<3>("011"))));
	entity.AddComponent(std::shared_ptr<ShootComp>(new ShootComp(0.3f, ProjectileComp::Target::Enemy, ProjectileComp::Type::Projectile)));
	entity.AddComponent(std::shared_ptr<HealthComp>(new HealthComp(12)));

	entity.hitbox.width = 12 * scale;
	entity.hitbox.height = 12  * scale;
	entity.hitbox.left = position.x + 3 * scale;
	entity.hitbox.top = position.y + 20 * scale;

	//debug name
	entity.name = "player";
	return entity;
}

Entity Assembler::CreateProjectile(sf::Vector2f position, sf::Vector2f direction, ProjectileComp::Target target, ProjectileComp::Type type, float speed)
{
	Entity entity(position, 50, sf::Vector2i(16, 16));

	std::shared_ptr<SpriteComp> spriteComp = std::shared_ptr<SpriteComp>(new SpriteComp(TextureHandler::TextureType::Projectiles, sf::IntRect(0, (int) type * 16, 16, 16), position));
	spriteComp->GetSprite().setOrigin(0, 7.5);
	spriteComp->GetSprite().scale(sf::Vector2f(0.75f, 0.75f));
	float angle = std::atan2(direction.y, direction.x) * (180 / M_PI);
	spriteComp->GetSprite().rotate(angle);
	entity.AddComponent(spriteComp);

	entity.AddComponent(std::shared_ptr<VelocityComp>(new VelocityComp(direction * speed * Tools::scale, direction)));
	entity.AddComponent(std::shared_ptr<ProjectileComp>(new ProjectileComp(target, type)));
	std::shared_ptr<CollisionComp> collisionComp = std::shared_ptr<CollisionComp>(new CollisionComp());
	collisionComp->SetCollision(Level::TileType::hole, false);
	entity.AddComponent(collisionComp);

	entity.hitbox = spriteComp->GetSprite().getGlobalBounds();
	entity.hitbox.height = 3 * Tools::scale;
	entity.hitbox.top += 6 * Tools::scale;

	entity.name = "projectile";
	return entity;
}

Entity Assembler::CreateSlime(sf::Vector2f position)
{
	Entity entity(position, 10, sf::Vector2i(16, 16));
	float scale = Tools::scale;

	entity.AddComponent(std::shared_ptr<AccelerationComp>(new AccelerationComp()));
	entity.AddComponent(std::shared_ptr<VelocityComp>(new VelocityComp()));
	std::shared_ptr<SpriteComp> spriteComp = std::shared_ptr<SpriteComp>(new SpriteComp(TextureHandler::TextureType::Slime, sf::IntRect(0, 0, entity.size.x, entity.size.y), position));
	entity.AddComponent(spriteComp);
	entity.AddComponent(std::shared_ptr<CollisionComp>(new CollisionComp()));
	entity.AddComponent(std::shared_ptr<HealthComp>(new HealthComp(4)));
	entity.AddComponent(std::shared_ptr<EnemyComp>(new EnemyComp(17.f * scale, 0.05f * scale)));
	entity.AddComponent(std::shared_ptr<AnimationComp>(new AnimationComp(entity.size, std::bitset<3>{ "010" })));

	entity.hitbox = spriteComp->GetSprite().getGlobalBounds();

	entity.name = "slime";
	return entity;
}

Entity Assembler::CreateGhost(sf::Vector2f position)
{
	Entity entity(position, 20, sf::Vector2i(16, 16));
	float scale = Tools::scale;
	entity.AddComponent(std::shared_ptr<AccelerationComp>(new AccelerationComp()));
	entity.AddComponent(std::shared_ptr<VelocityComp>(new VelocityComp()));
	std::shared_ptr<SpriteComp> spriteComp = std::shared_ptr<SpriteComp>(new SpriteComp(TextureHandler::TextureType::Ghost, position));
	entity.AddComponent(spriteComp);

	std::shared_ptr<CollisionComp> collisions = std::shared_ptr<CollisionComp>(new CollisionComp());
	collisions->SetCollision(Level::TileType::wall, false);
	collisions->SetCollision(Level::TileType::hole, false);

	entity.AddComponent(collisions);
	entity.AddComponent(std::shared_ptr<HealthComp>(new HealthComp(2)));
	entity.AddComponent(std::shared_ptr<EnemyComp>(new EnemyComp(15.f * scale, 0.05f * scale)));
	entity.AddComponent(std::shared_ptr<AnimationComp>(new AnimationComp(entity.size, std::bitset<3>{ "010" })));

	entity.hitbox = spriteComp->GetSprite().getGlobalBounds();
	entity.hitbox.width = 9 * scale;
	entity.hitbox.height = 11 * scale;
	entity.hitbox.left += 6 * scale;
	entity.hitbox.top += 3 * scale;

	entity.name = "ghost";
	return entity;
}
Entity Assembler::CreateBigZombie(sf::Vector2f position)
{
	Entity entity(position, 10, sf::Vector2i(32, 32));
	float scale = Tools::scale;

	entity.AddComponent(std::shared_ptr<AccelerationComp>(new AccelerationComp()));
	entity.AddComponent(std::shared_ptr<VelocityComp>(new VelocityComp()));
	std::shared_ptr<SpriteComp> spriteComp = std::shared_ptr<SpriteComp>(new SpriteComp(TextureHandler::TextureType::BigZombie, sf::IntRect(0, 0, 32, 32), position));
	entity.AddComponent(spriteComp);
	entity.AddComponent(std::shared_ptr<CollisionComp>(new CollisionComp()));
	entity.AddComponent(std::shared_ptr<HealthComp>(new HealthComp(10)));
	entity.AddComponent(std::shared_ptr<EnemyComp>(new EnemyComp(13.f * scale, 0.1f * scale)));
	entity.AddComponent(std::shared_ptr<AnimationComp>(new AnimationComp(entity.size, std::bitset<3>{ "011" })));

	entity.hitbox = spriteComp->GetSprite().getGlobalBounds();
	entity.hitbox.width = 18 * scale;
	entity.hitbox.height = 27 * scale;
	entity.hitbox.left += 7 * scale;
	entity.hitbox.top += 5 * scale;

	entity.name = "bigzombie";
	return entity;
}

Entity Assembler::CreateSkeleton(sf::Vector2f position)
{
	Entity entity(position, 10, sf::Vector2i(16, 32));

	float scale = Tools::scale;
	entity.AddComponent(std::shared_ptr<AccelerationComp>(new AccelerationComp()));
	entity.AddComponent(std::shared_ptr<VelocityComp>(new VelocityComp()));
	std::shared_ptr<SpriteComp> spriteComp = std::shared_ptr<SpriteComp>(new SpriteComp(TextureHandler::TextureType::Skeleton, sf::IntRect(0, 0, 16, 32), position));
	entity.AddComponent(spriteComp);
	entity.AddComponent(std::shared_ptr<CollisionComp>(new CollisionComp()));
	entity.AddComponent(std::shared_ptr<HealthComp>(new HealthComp(4)));
	entity.AddComponent(std::shared_ptr<EnemyComp>(new EnemyComp(20.f * scale, 0.05f * scale)));
	entity.AddComponent(std::shared_ptr<AnimationComp>(new AnimationComp(entity.size, std::bitset<3>{ "011" })));
	entity.AddComponent(std::shared_ptr<ShootComp>(new ShootComp(2.f, ProjectileComp::Target::Player, ProjectileComp::Type::Arrow)));

	entity.hitbox = spriteComp->GetSprite().getGlobalBounds();
	entity.hitbox.width = 10 * Tools::scale;
	entity.hitbox.height = 17 * Tools::scale;
	entity.hitbox.left += 1 * Tools::scale;
	entity.hitbox.top += 15 * Tools::scale;

	entity.name = "skeleton";
	return entity;
}

Entity Assembler::CreateCoin(sf::Vector2f position)
{
	Entity entity(position, 5, sf::Vector2i(8, 8));
	std::shared_ptr<SpriteComp> spriteComp = std::shared_ptr<SpriteComp>(new SpriteComp(TextureHandler::TextureType::Coin, sf::IntRect(0, 0, 8, 8), position));
	entity.AddComponent(spriteComp);
	entity.hitbox = spriteComp->GetSprite().getGlobalBounds();
	entity.AddComponent(std::shared_ptr<VelocityComp>(new VelocityComp()));
	entity.AddComponent(std::shared_ptr<CollisionComp>(new CollisionComp()));
	entity.AddComponent(std::shared_ptr<AnimationComp>(new AnimationComp(entity.size, std::bitset<3>{ "001" })));
	entity.AddComponent(std::shared_ptr<CollectableComp>(new CollectableComp(CollectableComp::Type::health)));

	entity.name = "coin";
	return entity;
}