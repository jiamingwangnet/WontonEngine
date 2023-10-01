#include "include/WontonEngine/Entity.h"

won::Entity::Entity(Game& game)
	: game{game}
{}

std::vector<won::Component*> won::Entity::GetComponents() const
{
	std::vector<won::Component*> ptrs;
	for (const std::unique_ptr<Component>& cmp : components)
	{
		ptrs.push_back(cmp.get());
	}

	return ptrs;
}

won::Game& won::Entity::GetGame() const
{
	return game;
}
