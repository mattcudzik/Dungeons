#pragma once
class Component
{
public:
	enum class ComponentType {
		PlayerControlled = 0,
		Velocity,
		Acceleration,
		Sprite,
		Collision,
		Animations,
		Projectile,
		LifeTime,
		Shoot,
		Health,
		Enemy,
		StaticAnimation,
		Collectable
	};

	//!!!ALWAYS UPDATE TypesAmount when adding new ComponentType
	const static int TypesAmount = 13;

	virtual ComponentType GetType() = 0 ;
};

