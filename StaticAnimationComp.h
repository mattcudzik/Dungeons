#pragma once
#include "Component.h"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Tools.h"

class StaticAnimationComp : public Component
{
public:
	enum AnimType
	{
		WalkFront = 0,
		WalkBack,
		WalkSide
	};
	
	ComponentType GetType();
	sf::IntRect GetFrame(AnimType type);
	StaticAnimationComp();
private:
	std::vector<sf::IntRect> m_frames;
};

