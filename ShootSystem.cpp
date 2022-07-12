#include "ShootSystem.h"
#include <iostream>

ShootSystem::ShootSystem() {}

void ShootSystem::Update(Entity& entity)
{
	if (entity.HasComponent(Component::ComponentType::Shoot))
	{
		std::shared_ptr<ShootComp> shootComp = std::dynamic_pointer_cast<ShootComp>(entity.GetComponent(Component::ComponentType::Shoot));
		sf::FloatRect hitbox = entity.hitbox;
		sf::Vector2f shootPosition = sf::Vector2f(hitbox.left + hitbox.width / 2, hitbox.top + hitbox.height / 2);
		std::shared_ptr<Level> currentLevel = LevelHandler::Instance().GetCurrentLevel();
		if (shootComp->GetElapsedTime() >= shootComp->GetCooldownTime())
		{
			if (shootComp->GetShootDirection() != sf::Vector2f(0.f,0.f))
			{
				float additionalSpeed = 0.f;

				std::normal_distribution<float> distribution(0, 0.05);
				sf::Vector2f randomDirection = sf::Vector2f(distribution(generator), distribution(generator));

				if (entity.HasComponent(Component::ComponentType::Velocity))
				{
					std::shared_ptr<VelocityComp> velocityComp = std::dynamic_pointer_cast<VelocityComp>(entity.GetComponent(Component::ComponentType::Velocity));
					if (velocityComp->GetDirection() == shootComp->GetShootDirection())
						additionalSpeed = Tools::MagnitudeOfVector(velocityComp->GetVelocity()) / Tools::scale * 0.6f ;
				}

				currentLevel->AddEntity(Assembler::Instance().CreateProjectile(shootPosition, Tools::NormalizeVector(shootComp->GetShootDirection() + randomDirection), shootComp->GetTarget(),shootComp->GetProjectileType(), shootComp->GetProjectileSpeed() + additionalSpeed));
				shootComp->ResetClock();
			}
		}
	}
}