#include "HealthComp.h"

Component::ComponentType HealthComp::GetType()
{
	return Component::ComponentType::Health;
}

HealthComp::HealthComp(int maxHealth) 
	:m_maxHealth(maxHealth), m_currentHealth(maxHealth), m_flashing(false), m_elapsedFlashingTime(0), m_flashingTime(2.f), changedColour(false), timeSinceLastFlash(0) {}

HealthComp::HealthComp(int maxHealth, float flashingTime)
	:m_maxHealth(maxHealth), m_currentHealth(maxHealth), m_flashing(false), m_elapsedFlashingTime(0), m_flashingTime(flashingTime), changedColour(false), timeSinceLastFlash(0)
{}

int HealthComp::GetCurrenHealth()
{
	return m_currentHealth;
}

int HealthComp::GetMaxHealth()
{
	return m_maxHealth;
}

void HealthComp::SetCurrenHealth(int health)
{
	m_currentHealth = health;
	if (m_currentHealth < 0)
		m_currentHealth = 0;
	if (m_currentHealth > m_maxHealth)
		m_currentHealth = m_maxHealth;
}

void HealthComp::CurrenHealth(int health)
{
	m_currentHealth += health;
	if (m_currentHealth < 0)
		m_currentHealth = 0;
	if (m_currentHealth > m_maxHealth)
		m_currentHealth = m_maxHealth;
}
bool HealthComp::IsFlashing()
{
	return this->m_flashing;
}
void HealthComp::SetFlashing(bool x = true)
{
	this->m_flashing = x;
}
float HealthComp::GetFlashingTime()
{
	return this->m_flashing;
}
void HealthComp::SetElapsedFlashingTime(float time)
{
	this->m_elapsedFlashingTime = time;
}
float HealthComp::GetElapsedFlashingTime()
{
	return this->m_elapsedFlashingTime;
}