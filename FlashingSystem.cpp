#include "FlashingSystem.h"

FlashingSystem::FlashingSystem(sf::Time deltaTime): deltaTime(deltaTime) {}


void FlashingSystem::Update(Entity& entity)
{
	if (entity.HasComponent(Component::ComponentType::Health))
	{
		std::shared_ptr<HealthComp> healthComp = std::dynamic_pointer_cast<HealthComp>(entity.GetComponent(Component::ComponentType::Health));
		if (healthComp->IsFlashing())
		{
			float elapsedTime = healthComp->GetElapsedFlashingTime();
			elapsedTime += deltaTime.asSeconds();
			if (elapsedTime >= healthComp->GetFlashingTime())
			{
				healthComp->SetElapsedFlashingTime(0);
				healthComp->SetFlashing(false);
				healthComp->timeSinceLastFlash = 0;
				if (healthComp->changedColour)
				{
					healthComp->changedColour = false;
					if (entity.HasComponent(Component::ComponentType::Sprite))
					{
						std::shared_ptr<SpriteComp> spriteComp = std::dynamic_pointer_cast<SpriteComp>(entity.GetComponent(Component::ComponentType::Sprite));
						spriteComp->GetSprite().setColor(sf::Color::White);
					}
				}
			}
			else
			{
				if (healthComp->timeSinceLastFlash > 0.05f)
				{
					if (entity.HasComponent(Component::ComponentType::Sprite))
					{
						std::shared_ptr<SpriteComp> spriteComp = std::dynamic_pointer_cast<SpriteComp>(entity.GetComponent(Component::ComponentType::Sprite));

						if (healthComp->changedColour)
						{
							spriteComp->GetSprite().setColor(sf::Color::White);
						}
						else
						{
							if (entity.HasComponent(Component::ComponentType::PlayerControlled))
								spriteComp->GetSprite().setColor(sf::Color::Black);
							if (entity.HasComponent(Component::ComponentType::Enemy))
								spriteComp->GetSprite().setColor(sf::Color::Red);
						}
						healthComp->changedColour = !healthComp->changedColour;
					}

					healthComp->timeSinceLastFlash = 0;
				}
				else
					healthComp->timeSinceLastFlash += deltaTime.asSeconds();
				healthComp->SetElapsedFlashingTime(elapsedTime);
				
			}
		}
	}
}