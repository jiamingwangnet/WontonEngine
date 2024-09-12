#pragma once

#include "Entity.h"

namespace won
{
	class Component
	{
	public:
		Component(Entity entity, Game* game);
		Component() = default;

	protected:
		Entity entity;
		Game* game;
	};
}