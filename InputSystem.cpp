#include "InputSystem.h"

void InputSystem::Update(Entity& entity) 
{
	if (entity.HasComponent(Component::ComponentType::PlayerControlled))
	{
		if (entity.HasComponent(Component::ComponentType::Acceleration) && entity.HasComponent(Component::ComponentType::Velocity))
		{
			std::shared_ptr<AccelerationComp> accelComp = std::dynamic_pointer_cast<AccelerationComp>(entity.GetComponent(Component::ComponentType::Acceleration));
			std::shared_ptr<VelocityComp> velocityComp = std::dynamic_pointer_cast<VelocityComp>(entity.GetComponent(Component::ComponentType::Velocity));
			std::shared_ptr<PlayerControlledComp> playerComp = std::dynamic_pointer_cast<PlayerControlledComp>(entity.GetComponent(Component::ComponentType::PlayerControlled));

			sf::Vector2f direction = sf::Vector2f(0, 0);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				direction.y = 1.0f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				direction.y = -1.0f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				direction.x = 1.0f;
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				direction.x = -1.0f;
			}

			direction = Tools::NormalizeVector(direction);

			velocityComp->SetDirection(direction);
			accelComp->SetAcceleration((direction * playerComp->GetMaxSpeed() - velocityComp->GetVelocity()) * playerComp->GetAcceleration());
		}

		if (entity.HasComponent(Component::ComponentType::Shoot))
		{
			std::shared_ptr<ShootComp> shootComp = std::dynamic_pointer_cast<ShootComp>(entity.GetComponent(Component::ComponentType::Shoot));
			sf::Vector2f direction;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				direction = sf::Vector2f(0.f, 1.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				direction = sf::Vector2f(0.f, -1.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			{
				direction = sf::Vector2f(-1.f, 0.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				direction = sf::Vector2f(1.f, 0.f);
			}
			else
			{
				direction = sf::Vector2f(0.f, 0.f);
			}
			shootComp->SetShootDirection(direction);
		}
	}

	
}
