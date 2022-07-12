#include "Entity.h"

#include "SpriteComp.h"
#include "HealthComp.h"
#include "Level.h"
#include "LevelHandler.h"
#include "HUD.h"
#include "RankingHandler.h"

#include "GameHandler.h"
void Entity::AddComponent(std::shared_ptr<Component> component) 
{
	componentFlags.set((int)component->GetType(), true);
	components.emplace_back(component);
}

void Entity::Draw(sf::RenderWindow& window)
{
	window.draw(std::dynamic_pointer_cast<SpriteComp>(GetComponent(Component::ComponentType::Sprite))->GetSprite());
}

Entity::Entity(sf::Vector2f position, int layer, sf::Vector2i size): toDelete(false), ID(IDcounter()), m_layer(layer), size(size) 
{
	this->position = position;
	this->position.y += size.y * Tools::scale;
}

bool Entity::HasComponent(Component::ComponentType type)
{
	return componentFlags[(int)type];
}
std::shared_ptr<Component> Entity::GetComponent(Component::ComponentType type)
{
	for (auto comp : components)
	{
		if (comp->GetType() == type)
			return comp;
	}

	return nullptr;
}

void Entity::Move(sf::Vector2f vector)
{
	position += vector;
	hitbox.left += vector.x;
	hitbox.top += vector.y;
	if (HasComponent(Component::ComponentType::Sprite))
	{
		std::shared_ptr<SpriteComp> spriteComp = std::dynamic_pointer_cast<SpriteComp>(GetComponent(Component::ComponentType::Sprite));
		spriteComp->GetSprite().move(vector);
	}
}
int Entity::GetLayer()
{
	return this->m_layer;
}
void Entity::SetToDelete()
{
	this->toDelete = true;
}
bool Entity::GetToDelete()
{
	return this->toDelete;
}
void Entity::SetEntityHealth(int amount)
{
	if (HasComponent(Component::ComponentType::Health))
	{
		std::shared_ptr<HealthComp> healthComp = std::dynamic_pointer_cast<HealthComp>(GetComponent(Component::ComponentType::Health));
		if (amount > 0)
		{
			healthComp->CurrenHealth(amount);
			if (HasComponent(Component::ComponentType::PlayerControlled))
				HUD::UpdateHealthPoints();
		}
		else
			if (!healthComp->IsFlashing())
			{
				healthComp->CurrenHealth(amount);
				if (HasComponent(Component::ComponentType::PlayerControlled))
					HUD::UpdateHealthPoints();
				healthComp->SetFlashing(true);

				if (healthComp->GetCurrenHealth() <= 0)
				{
					SetToDelete();
					OnDeath();
				}

			}
	}
}

void Entity::OnDeath()
{
	if (HasComponent(Component::ComponentType::PlayerControlled))
	{
		HUD::ShowMessage();
		HUD::waitForEnter = true;
	}
	else if (HasComponent(Component::ComponentType::Enemy))
	{
		RankingHandler::Instance().AddPoints(50);
		LevelHandler::Instance().GetCurrentLevel()->enemiesAmount--;
		if (LevelHandler::Instance().GetCurrentLevel()->enemiesAmount == 0)
		{
			LevelHandler::Instance().SpawnLadder();
		}
		sf::Vector2f coinPos = sf::Vector2f(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2);
		LevelHandler::Instance().GetCurrentLevel()->AddEntity(Assembler::Instance().CreateCoin(coinPos));
	}
}