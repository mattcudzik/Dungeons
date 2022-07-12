#include "AnimationComp.h"

Component::ComponentType AnimationComp::GetType()
{
	return Component::ComponentType::Animations;
}
AnimationComp::AnimType AnimationComp::GetCurrenAnimType()
{
	return this->curentAnim;
}
//TMP 
AnimationComp::AnimationComp(sf::Vector2i size, std::bitset<3> availableAnimations):  elapsedTime(0), availableAnimations(availableAnimations)
{
	int counter = 0;
	for (int i = 0; i < 3; i++)
	{
		if (availableAnimations[i])
		{
			animations[(AnimType)i] = std::shared_ptr<Animation>(new Animation(counter, size));
			curentAnim = (AnimType) i;
			counter++;
		}
			
	}
}
float AnimationComp::GetElapsedTime()
{
	return this->elapsedTime;
}
void AnimationComp::UpdateElapsedTime(float time)
{
	this->elapsedTime += time;
}
void AnimationComp::ResetElapsedTime()
{
	this->elapsedTime = 0;
}

std::shared_ptr<Animation> AnimationComp::GetCurrenAnim()
{
	return this->animations[this->curentAnim];
}
void AnimationComp::SetCurrentAnim(AnimType type)
{
	this->animations[this->curentAnim]->ResetAnimation();
	if(availableAnimations[type])
		this->curentAnim = type;
	this->elapsedTime = 0;
}