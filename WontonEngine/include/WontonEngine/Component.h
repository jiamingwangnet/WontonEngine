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

		/*
		* Virtual Functions
		* 
			static void Init(Component& self) {};
			static void Update(Component& self) {};
			static void RUpdate(Component& self) {};
			static void OnDestroy(Component& self) {};
		*/

	protected:
		Entity entity = INVALID_ENTITY;
		Game* game = nullptr;
	};
}