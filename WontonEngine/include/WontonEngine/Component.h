#pragma once

#include "Entity.h"

namespace won
{
	class Component
	{
	public:
		Component(Entity entity);
		Component() = default;

	protected:
		Entity entity;
	};
}