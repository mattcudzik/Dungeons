#pragma once
#include "Component.h"
#include "SFML/System.hpp"

class HealthComp : public Component
{
private:
	int m_currentHealth;
	int m_maxHealth;

	float m_flashingTime;
	float m_elapsedFlashingTime;
	bool m_flashing;
public:
	ComponentType GetType();
	HealthComp(int maxHealth);
	HealthComp(int maxHealth, float flashingTime);
	int GetCurrenHealth();
	int GetMaxHealth();
	void SetCurrenHealth(int health);
	//Adds to current health without overriding
	void CurrenHealth(int health);
	bool IsFlashing();
	void SetFlashing(bool x);
	float GetFlashingTime();
	void SetElapsedFlashingTime(float time);
	float GetElapsedFlashingTime();

	bool changedColour;
	float timeSinceLastFlash;
};

