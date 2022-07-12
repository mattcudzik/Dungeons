#include "ProjectileSystem.h"

#include "ProjectileComp.h"
#include "HealthComp.h"
#include "SpriteComp.h"




void ProjectileSystem::Update(Entity& entity)
{
	if (entity.HasComponent(Component::ComponentType::Projectile))
	{
		std::shared_ptr<ProjectileComp> projectileComp = std::dynamic_pointer_cast<ProjectileComp>(entity.GetComponent(Component::ComponentType::Projectile));
		std::vector<std::shared_ptr<Entity>>& entities = LevelHandler::Instance().GetCurrentLevel()->GetEntities();

		sf::FloatRect projectileHitbox = entity.hitbox;

		ProjectileComp::Target target = projectileComp->GetProjectileTarget();

		std::ranges::for_each(entities, [&](auto& entityPtr)
			{
				if (!entityPtr->HasComponent(Component::ComponentType::Collision))
					return;
				if (!entityPtr->hitbox.intersects(projectileHitbox))
					return;
				if (!entityPtr->HasComponent(Component::ComponentType::Health))
					return;

				if (entityPtr->HasComponent(Component::ComponentType::Enemy) && target == ProjectileComp::Target::Enemy || entityPtr->HasComponent(Component::ComponentType::PlayerControlled) && target == ProjectileComp::Target::Player)
				{
					entity.SetToDelete();
					entityPtr->SetEntityHealth(-1);
				}
				
			});

		/*for (auto & entityPtr : entities)
		{
			if (!entityPtr->HasComponent(Component::ComponentType::Collision))
				continue;
			if (!entityPtr->hitbox.intersects(projectileHitbox))
				continue;
			if (!entityPtr->HasComponent(Component::ComponentType::Health))
				continue;

			
			if (entityPtr->HasComponent(Component::ComponentType::Enemy) && target == ProjectileComp::Target::Enemy || entityPtr->HasComponent(Component::ComponentType::PlayerControlled) && target == ProjectileComp::Target::Player)
			{
				entity.SetToDelete();
				entityPtr->DamageEntity(1);
			}
			
		}*/
	}
}