#pragma once

#include <string>
#include "EntityCreator.h"

namespace won
{
	class Defaults
	{
	public:
		static void Load(const std::string& name);

	public:
		class Box : public EntityCreator
		{
		private:
			void Create(Entity& entity) const override;
		};
	};
}