#include "StaticAnimationComp.h"
Component::ComponentType StaticAnimationComp::GetType()
{
	return Component::ComponentType::StaticAnimation;
}


sf::IntRect StaticAnimationComp::GetFrame(AnimType type)
{
	return m_frames[type];
}

//TMP Constructor
StaticAnimationComp::StaticAnimationComp()
{
	/*for (int i = 0; i < 3; i++)
	{
		m_frames.push_back(sf::IntRect(0, i * Tools::characterSpriteSize, Tools::characterSpriteSize, Tools::characterSpriteSize));
	}*/
}