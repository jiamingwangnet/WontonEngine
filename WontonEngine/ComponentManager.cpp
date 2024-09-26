#include "include/WontonEngine/ComponentManager.h"
#include "include/WontonEngine/Entity.h"
#include "include/WontonEngine/Game.h"

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

void won::priv::ComponentManager::RUpdateComponents()
{
	// loop through arrays and call update
	for (auto& cmp : components)
	{
		cmp.second->RUpdateComponents();
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

void won::priv::ComponentManager::SetActiveGame(Game* game)
{
	this->game = game;
}

won::Game* won::priv::ComponentManager::GetActiveGame() const
{
	return game;
}