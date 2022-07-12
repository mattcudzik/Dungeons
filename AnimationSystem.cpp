#include "AnimationSystem.h"

#include "Animation.h"
#include "AnimationComp.h"
#include "StaticAnimationComp.h"
#include "SpriteComp.h"
#include "AccelerationComp.h"
#include "VelocityComp.h"


AnimationSystem::AnimationSystem(sf::Time dTime): deltaTime(dTime) {}

void AnimationSystem::Update(Entity& entity)
{
	if (entity.HasComponent(Component::ComponentType::Animations))
	{
		std::shared_ptr<SpriteComp> spriteComp = std::dynamic_pointer_cast<SpriteComp>(entity.GetComponent(Component::ComponentType::Sprite));
		std::shared_ptr<AnimationComp> animationComp = std::dynamic_pointer_cast<AnimationComp>(entity.GetComponent(Component::ComponentType::Animations));

		if (entity.HasComponent(Component::ComponentType::Velocity))
		{
			std::shared_ptr<VelocityComp> velocityComp = std::dynamic_pointer_cast<VelocityComp>(entity.GetComponent(Component::ComponentType::Velocity));

			sf::Vector2f direction = velocityComp->GetDirection();

			if (direction.x > 0.f)
			{
				spriteComp->FlipXSprite(false);
			}
			else if (direction.x < 0.f)
			{
				spriteComp->FlipXSprite(true);
			}
			float velocityAnimationCap = 10 * Tools::scale;
			if (Tools::MagnitudeOfVector(velocityComp->GetVelocity()) > velocityAnimationCap)
			{
				if(animationComp->GetCurrenAnimType() != AnimationComp::AnimType::Walk)
					animationComp->SetCurrentAnim(AnimationComp::AnimType::Walk);	
			}
			else 
			{
				if (animationComp->GetCurrenAnimType() != AnimationComp::AnimType::Idle)
					animationComp->SetCurrentAnim(AnimationComp::AnimType::Idle);
			}
		}

		if (animationComp->GetElapsedTime() > animationComp->GetCurrenAnim()->frameTime)
		{
			animationComp->ResetElapsedTime();
			spriteComp->SetSprite(animationComp->GetCurrenAnim()->GetNextFrame());
		}
		else
			animationComp->UpdateElapsedTime(deltaTime.asSeconds());


	}
}