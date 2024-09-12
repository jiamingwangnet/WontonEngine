#pragma once

namespace won
{
	class Entity;

	namespace priv
	{
		class ComponentManager;
		class EntityManager;

		// middle-man
		class ECManager
		{
		private:
			static ComponentManager& GetComponentManager();
			static EntityManager& GetEntityManager();

			friend class Entity;
		};
	}
}