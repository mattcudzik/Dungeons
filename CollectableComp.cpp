#include "CollectableComp.h"

Component::ComponentType CollectableComp::GetType()
{
	return Component::ComponentType::Collectable;
}
CollectableComp::CollectableComp(Type collectableType) : m_collectableType(collectableType) {}

CollectableComp::Type CollectableComp::GetCollectableType()
{
	return this->m_collectableType;
}