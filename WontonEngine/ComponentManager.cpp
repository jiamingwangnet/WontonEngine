#include "include/WontonEngine/ComponentManager.h"
#include "include/WontonEngine/Entity.h"

void won::priv::ComponentManager::InitComponents()
{
	// loop through arrays and call init
	for (auto& cmp : components)
	{
		cmp.second->InitComponents();
	}
}

void won::priv::ComponentManager::UpdateComponents()
{
	// loop through arrays and call update
	for (auto& cmp : components)
	{
		cmp.second->UpdateComponents();
	}
}

void won::priv::ComponentManager::EntityDestroyed(Entity entity)
{
	// loop through component arrays and call their EntityDestroyed
	for (auto& cmp : components)
	{
		cmp.second->EntityDestroyed(entity);
	}
}
