#pragma once

#include <vector>
#include <array>
#include <functional>
#include <unordered_map>
#include "Constants.h"
#include "ECManager.h"

namespace won
{
	class Entity;
	class Game;

	namespace priv
	{
		using EntId = unsigned int;

		class IComponentArray
		{
		public:
			IComponentArray() = default;
			virtual ~IComponentArray() = default;

			// for the component manager to update and init
			virtual void InitComponents() = 0;
			virtual void UpdateComponents() = 0;
			virtual void RUpdateComponents() = 0;

			virtual void EntityDestroyed(EntId entity) = 0;
		};

		template<class T>
		class ComponentArray : public IComponentArray
		{
		public:
			ComponentArray();

			template<class ...Args>
			void Insert(EntId entity, Game* activeGame, Args&& ...args);
			void Remove(EntId entity);
			T& Retrieve(EntId entity);

			void EntityDestroyed(EntId entity) override;

			// for the component manager to update and init
			void InitComponents() override;
			void UpdateComponents() override;
			void RUpdateComponents() override;

		private:
			static constexpr std::size_t INVALID_INDEX = (std::size_t)-1;

			// store components of type T's properties (using array as we do not need to allocate on the heap)
			std::array<T, MAX_ENTITIES> components{};

			// keeps track of uninitialized components
			std::vector<std::size_t> newComponents{};

			// store functions
			void (*finit)(T&) = &T::Init;
			void (*fupdate)(T&) = &T::Update;
			void (*frupdate)(T&) = &T::RUpdate;
			void (*fondestroy)(T&) = &T::OnDestroy;

			// map from entity id to array index
			std::array<std::size_t, MAX_ENTITIES> entityToIndexMap{};
			// reverse
			std::array<EntId, MAX_ENTITIES> indexToEntityMap{};

			std::size_t size = 0;
		};

		template<class T>
		template<class ...Args>
		inline void ComponentArray<T>::Insert(EntId entity, Game* activeGame, Args && ...args)
		{
			components[size] = T{ entity, activeGame, std::forward<Args>(args)... };
			entityToIndexMap[entity] = size;
			indexToEntityMap[size] = entity;
			newComponents.push_back(size);

			size++;
		}

		template<class T>
		inline ComponentArray<T>::ComponentArray()
		{
			for (std::size_t i = 0; i < MAX_ENTITIES; i++)
				entityToIndexMap[i] = INVALID_INDEX;

			for (std::size_t i = 0; i < MAX_ENTITIES; i++)
				indexToEntityMap[i] = INVALID_ENTITY;
		}

		template<class T>
		inline void ComponentArray<T>::Remove(EntId entity)
		{
			// remove the component for the specified entity
			// ensure components are stored contiguously 
			// copy last components to the removed components	
			// change the mapping
			std::size_t index = entityToIndexMap[entity];

			// call onDestroy
			fondestroy(components[index]);

			components[index] = components[size - 1];
			entityToIndexMap[indexToEntityMap[size - 1]] = index;
			indexToEntityMap[index] = indexToEntityMap[size - 1];

			entityToIndexMap[entity] = INVALID_INDEX;
			indexToEntityMap[size - 1] = INVALID_ENTITY;

			size--;
		}

		template<class T>
		inline T& ComponentArray<T>::Retrieve(EntId entity)
		{
			return components[entityToIndexMap[entity]];
		}

		template<class T>
		inline void ComponentArray<T>::EntityDestroyed(EntId entity)
		{
			// check if the entity has the specified component
			// call Remove to remove the component
			if (entityToIndexMap[entity] != INVALID_INDEX)
			{
				Remove(entity);
			}
		}

		template<class T>
		inline void ComponentArray<T>::InitComponents()
		{
			// loop through list and clear afterwards
			for (std::size_t& idx : newComponents)
			{
				finit(components[idx]);
			}
		}
		template<class T>
		inline void ComponentArray<T>::UpdateComponents()
		{
			// updates all components
			for (int i = 0; i < size; i++)
			{
				fupdate(components[i]);
			}
		}
		template<class T>
		inline void ComponentArray<T>::RUpdateComponents()
		{
			// updates all components
			for (int i = 0; i < size; i++)
			{
				frupdate(components[i]);
			}
		}
	}
}