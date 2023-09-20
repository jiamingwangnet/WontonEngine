#pragma once

#include "Component.h"
#include <vector>
#include <memory>

namespace won
{
	class Game;

	class Entity
	{
	public:
		Entity(Game& game);

		template<class Cmp>
		Cmp* GetComponent() const;

		template<class Cmp, class... Args>
		Cmp* AddComponent(Args&&... args);

		std::vector<Component*> GetComponents() const;

	private:
		Game& game;
		std::vector<std::unique_ptr<Component>> components;
	};
}