#pragma once

#include <unordered_map>
#include <memory>
#include "ComponentArray.h"

#define CAST_T(x) std::static_pointer_cast<ComponentArray<T>>(x)

namespace won
{
	class Entity;
	class Game;

	namespace priv
	{
		class ComponentManager
		{
		public:
			template<class T>
			void RegisterComponent(); // should assign an ID to the component

			template<class T>
			unsigned int GetComponentId();

			template<class T>
			T& GetComponent(EntId id);

			template<class T>
			void RemoveComponent(EntId id);

			template<class T, class ...Args>
			void AddComponent(EntId id, Args&& ...args);

			void InitComponents();
			void UpdateComponents();
			void RUpdateComponents();

			void EntityDestroyed(EntId entity);

			void SetActiveGame(Game* game);
			Game* GetActiveGame() const;

		private:
			// type hash, component array
			std::unordered_map<std::size_t, std::shared_ptr<IComponentArray>> components;

			unsigned int ncomponents = 0;
			std::unordered_map<std::size_t, unsigned int> componentToId;

			Game* game = nullptr;
		};

		template<class T>
		inline void ComponentManager::RegisterComponent()
		{
			std::size_t hash = typeid(T).hash_code();
			// will do checking
			components.insert({ hash, std::make_shared<ComponentArray<T>>() });
			componentToId.insert({ hash, ncomponents });
			ncomponents++;
		}

		template<class T>
		inline unsigned int ComponentManager::GetComponentId()
		{
			return componentToId.at(typeid(T).hash_code());
		}

		template<class T>
		inline T& ComponentManager::GetComponent(EntId id)
		{
			return CAST_T(components[typeid(T).hash_code()])->Retrieve(id);
		}

		template<class T>
		inline void ComponentManager::RemoveComponent(EntId id)
		{
			return CAST_T(components[typeid(T).hash_code()])->Remove(id);
		}

		template<class T, class ...Args>
		inline void ComponentManager::AddComponent(EntId id, Args && ...args)
		{
			CAST_T(components[typeid(T).hash_code()])->Insert(id, game, std::forward<Args>(args)...);
		}
	}
}