#pragma once

#include "Entity.h"

namespace won
{
	class Component
	{
	public:
		Component(Entity entity, Game* game);
		Component() = default;

		Entity GetEntity() const { return entity; }
	protected:
		Entity entity = INVALID_ENTITY;
		Game* game = nullptr;
	};
}