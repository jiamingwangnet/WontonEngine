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

		Game& GetGame() const;

	private:
		Game& game;
		std::vector<std::unique_ptr<Component>> components;
	};

	template<class Cmp>
	inline Cmp* Entity::GetComponent() const
	{
		for (const std::unique_ptr<Component>& cmp : components)
		{
			if (typeid(Cmp) == typeid(*cmp))
			{
				return static_cast<Cmp*>(cmp.get());
			}
		}
		return nullptr;
	}

	template<class Cmp, class ...Args>
	inline Cmp* Entity::AddComponent(Args&& ...args)
	{
		components.push_back(std::make_unique<Cmp>(*this, std::forward<Args>(args)...));
		components.back()->Init();

		return static_cast<Cmp*>(components.back().get());
	}
}