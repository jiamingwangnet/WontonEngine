#pragma once

#include <vector>
#include <array>
#include <functional>
#include <unordered_map>
#include "Constants.h"

namespace won
{
	class Entity;

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

			virtual void EntityDestroyed(Entity entity) = 0;
		};

		template<class T>
		class ComponentArray : public IComponentArray
		{
		public:
			ComponentArray() = default;

			template<class ...Args>
			void Insert(EntId entity, Args&& ...args);
			void Remove(EntId entity);
			T& Retrieve(EntId entity);

			void EntityDestroyed(Entity entity) override;

			// for the component manager to update and init
			void InitComponents() override;
			void UpdateComponents() override;

		private:
			// store components of type T's properties (using array as we do not need to allocate on the heap)
			std::array<T, MAX_ENTITIES> components{};

			// keeps track of uninitialized components
			std::vector<std::size_t> newComponents{};

			// store functions
			void (*finit)(T&) = &T::Init;
			void (*fupdate)(T&) = &T::Update;

			// map from entity id to array index
			std::unordered_map<EntId, std::size_t> entityToIndexMap{};
			// reverse
			std::unordered_map<std::size_t, EntId> indexToEntityMap{};

			std::size_t size = 0;
		};

		template<class T>
		template<class ...Args>
		inline void ComponentArray<T>::Insert(EntId entity, Args && ...args)
		{
			components[size] = T{ (Entity)entity, std::forward<Args>(args)... };
			entityToIndexMap[entity] = size;
			indexToEntityMap[size] = entity;
			newComponents.push_back(size);

			size++;
		}

		template<class T>
		inline void ComponentArray<T>::Remove(EntId entity)
		{
			// remove the component for the specified entity
			// ensure components are stored contiguously 
			// copy last components to the removed components	
			// change the mapping
			std::size_t index = entityToIndexMap[entity];
			components[index] = components[size - 1];
			entityToIndexMap[indexToEntityMap[size - 1]] = index;
			indexToEntityMap[index] = indexToEntityMap[size - 1];

			entityToIndexMap.erase(entity);
			indexToEntityMap.erase(size - 1);

			size--;
		}

		template<class T>
		inline T& ComponentArray<T>::Retrieve(EntId entity)
		{
			return components[entityToIndexMap[entity]];
		}

		template<class T>
		inline void ComponentArray<T>::EntityDestroyed(Entity entity)
		{
			// check if the entity has the specified component
			// call Remove to remove the component
			if (entityToIndexMap.find(entity.GetId()) != entityToIndexMap.end())
			{
				Remove(entity.GetId());
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
	}
}