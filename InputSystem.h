#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "System.h"
#include "Entity.h"
#include "Tools.h"

#include "PlayerControlledComp.h"
#include "AccelerationComp.h"
#include "VelocityComp.h"
#include "ShootComp.h"

class InputSystem : public System
{
public:
	void Update(Entity& entity);
};

