#pragma once

#include <bitset>
#include <queue>
#include "Entity.h"
#include "ComponentManager.h"
#include <unordered_set>

namespace won
{
	namespace priv
	{
		using Signature = std::bitset<MAX_COMPONENTS>;

		class EntityManager
		{
		public:
			EntityManager(ComponentManager& componentManager);

			Entity CreateEntity();
			void DestroyEntity(Entity entity);
			void Clear();

			// the entity's id is used to index into this array
			void SetSignature(Entity entity, Signature sig);
			Signature GetSignature(Entity entity);

		private:
			std::queue<Entity> availableIds;
			std::array<Signature, MAX_ENTITIES> signatures; // use array for less overhead
			unsigned int entities = 0;
			ComponentManager& componentManager;
			std::unordered_set<EntId> created{};
		};
	}
}