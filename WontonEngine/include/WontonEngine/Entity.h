#pragma once

#include <vector>
#include <memory>
#include <utility>
#include "ECManager.h"
#include "ComponentManager.h"
#include "Constants.h"

namespace won
{
	class Game;
	class Component;

	class Entity
	{
	public:
		Entity();
		Entity(const EntId& id);

		template<class Cmp>
		Cmp* GetComponent() const;

		template<class Cmp, class... Args>
		Cmp* AddComponent(Args&&... args);

		std::vector<Component*> GetComponents() const;

		EntId GetId() const;
	private:
		EntId id;
	};

	template<class Cmp>
	inline Cmp* Entity::GetComponent() const
	{
		return &priv::ECManager::GetComponentManager().GetComponent<Cmp>(id);
	}

	template<class Cmp, class ...Args>
	inline Cmp* Entity::AddComponent(Args&& ...args)
	{
		priv::ECManager::GetComponentManager().AddComponent<Cmp>(id, std::forward<Args>(args)...);
		return &priv::ECManager::GetComponentManager().GetComponent<Cmp>(id);
	}
}