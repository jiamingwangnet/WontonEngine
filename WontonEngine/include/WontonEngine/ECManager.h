#pragma once

namespace won
{
	class Entity;

	namespace priv
	{
		class ComponentManager;
		class EntityManager;
		template<class T>
		class ComponentArray;

		// middle-man
		class ECManager
		{
		private:
			static ComponentManager& GetComponentManager();
			static EntityManager& GetEntityManager();

			friend class won::Entity;
			friend class ComponentManager;
			friend class EntityManager;
			template<class T>
			friend class ComponentArray;
		};
	}
}