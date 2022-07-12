#include "EnemySystem.h"

#include "EnemyComp.h"
#include "AccelerationComp.h"
#include "VelocityComp.h"
#include "ShootComp.h"


const float avoidanceDistance = 10 * Tools::scale;
const float shootRangeDistnace = 100 * Tools::scale;

void EnemySystem::Update(Entity& entity)
{
	if (entity.HasComponent(Component::ComponentType::Enemy))
	{
		std::shared_ptr<EnemyComp> enemyComp = std::dynamic_pointer_cast<EnemyComp>(entity.GetComponent(Component::ComponentType::Enemy));

		if (entity.HasComponent(Component::ComponentType::Acceleration) && entity.HasComponent(Component::ComponentType::Velocity))
		{
			std::shared_ptr<AccelerationComp> accelComp = std::dynamic_pointer_cast<AccelerationComp>(entity.GetComponent(Component::ComponentType::Acceleration));
			std::shared_ptr<VelocityComp> velocityComp = std::dynamic_pointer_cast<VelocityComp>(entity.GetComponent(Component::ComponentType::Velocity));
			

			sf::Vector2f direction;
			//random movement
			/*
			srand((int)time(0));
			if (enemyComp->testClock.getElapsedTime().asSeconds() >= 1.f)
			{
				direction.x = rand() % 3 - 1;
				direction.y = rand() % 3 - 1;

				velocityComp->SetDirection(direction);

				enemyComp->testClock.restart();
			}
			else
			{
				direction = velocityComp->GetDirection();
			}*/
			//following player
			sf::Vector2f playerPosition = LevelHandler::Instance().GetCurrentLevel()->player->position;
			direction.x = playerPosition.x - entity.position.x;
			direction.y = playerPosition.y - entity.position.y;


			//BOIDS BEHAVIOUR - avoidance of nearby enemies
			//Considers only last entity checked! FIX(?)
			std::vector<std::shared_ptr<Entity>>& entities = LevelHandler::Instance().GetCurrentLevel()->GetEntities();
			
			sf::Vector2f initialDirection = direction;
			for (auto ptr : entities)
			{
				if (!ptr->HasComponent(Component::ComponentType::Enemy))
					continue;
				if (ptr->ID == entity.ID)
					continue;

				float enemyDistance = Tools::MagnitudeOfVector(entity.position - ptr->position);
				
				if (enemyDistance < avoidanceDistance && enemyDistance != 0.f)
				{
					direction = entity.position - ptr->position;
				}

			}

			direction = Tools::NormalizeVector(direction);

			if (entity.HasComponent(Component::ComponentType::Shoot))
			{
				//check if within range to stop and shoot
				float playerDistance = Tools::MagnitudeOfVector(entity.position - playerPosition);
				//std::sqrt(std::pow(entity.position.x - playerPosition.x, 2) + std::pow(entity.position.y - playerPosition.y, 2));
				std::shared_ptr<ShootComp> shootComp = std::dynamic_pointer_cast<ShootComp>(entity.GetComponent(Component::ComponentType::Shoot));
				if (playerDistance < shootRangeDistnace)
				{
					direction = sf::Vector2f(0.f, 0.f);
					initialDirection = direction;
					shootComp->SetShootDirection(Tools::NormalizeVector(playerPosition - entity.position));
				}
				else
				{
					shootComp->SetShootDirection(sf::Vector2f(0.f, 0.f));
				}
			}
			
			sf::Vector2f acceleration = (direction * enemyComp->GetMaxSpeed() - velocityComp->GetVelocity()) * enemyComp->GetAcceleration();
			velocityComp->SetDirection(initialDirection);
			accelComp->SetAcceleration(acceleration);
			

		}

	}
}