#pragma once

#include "Entity.h"
#include "Game.h"

namespace won
{
	class EntityCreator
	{
	private:
		virtual void Create(Entity& entity) const = 0;

		friend class Game;
	};
}