#pragma once
#include "Component.h"
#include "Animation.h"

#include <vector>
#include <map>
#include <bitset>

#include "SFML/System.hpp"

class AnimationComp : public Component
{
public:
	enum AnimType
	{
		Idle = 0,
		Walk,
		Damage
	};
	ComponentType GetType();
	AnimationComp(sf::Vector2i size, std::bitset<3> availableAnimations);
	float GetElapsedTime();
	void UpdateElapsedTime(float time);
	void ResetElapsedTime();
	std::shared_ptr<Animation> GetCurrenAnim();
	AnimType GetCurrenAnimType();
	void SetCurrentAnim(AnimType type);
	const std::bitset<3> availableAnimations;
private:
	AnimType curentAnim;
	float elapsedTime;
	std::map<AnimType, std::shared_ptr<Animation>> animations;
};

