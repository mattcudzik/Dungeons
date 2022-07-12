#pragma once
#include "Component.h"
class CollectableComp : public Component
{
public:
	ComponentType GetType();
	enum Type
	{
		health,
		points
	}; 

	CollectableComp(Type collectableType);
	Type GetCollectableType();

private:
		Type m_collectableType;
};

