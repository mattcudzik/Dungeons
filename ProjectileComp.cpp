#include "ProjectileComp.h"

Component::ComponentType ProjectileComp::GetType()
{
	return Component::ComponentType::Projectile;
}
ProjectileComp::Target ProjectileComp::GetProjectileTarget()
{
	return this->m_target;
}
ProjectileComp::Type ProjectileComp::GetProjectileType()
{
	return this->m_type;
}
ProjectileComp::ProjectileComp(Target target, Type type) : m_target(target), m_type(type) {}