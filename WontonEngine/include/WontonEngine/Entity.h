#pragma once

#include <vector>
#include <memory>
#include <utility>
//#include <cassert>
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

		template<class Cmp>
		void RemoveComponent() const;

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

	template<class Cmp>
	inline void Entity::RemoveComponent() const
	{
		priv::ComponentManager& cmpManager = priv::ECManager::GetComponentManager();
		priv::EntityManager& entityManager = priv::ECManager::GetEntityManager();
		cmpManager.RemoveComponent<Cmp>(id);
		entityManager.SetSignature(*this, entityManager.GetSignature(*this).reset((std::size_t)cmpManager.GetComponentId<Cmp>()));
	}

	template<class Cmp, class ...Args>
	inline Cmp* Entity::AddComponent(Args&& ...args)
	{
		priv::ComponentManager& cmpManager = priv::ECManager::GetComponentManager();
		priv::EntityManager& entityManager = priv::ECManager::GetEntityManager();
		cmpManager.AddComponent<Cmp>(id, std::forward<Args>(args)...);
		entityManager.SetSignature(*this, entityManager.GetSignature(*this).set((std::size_t)cmpManager.GetComponentId<Cmp>()));
		
		//assert(entityManager.GetSignature(*this)[(cmpManager.GetComponentId<Cmp>())]);

		return &cmpManager.GetComponent<Cmp>(id);
	}
}