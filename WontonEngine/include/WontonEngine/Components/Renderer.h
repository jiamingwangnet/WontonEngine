#pragma once

#include "../Component.h"
#include "../Rendering/Material.h"
#include "../Rendering/Mesh.h"

namespace won
{
	namespace cmp
	{
		class Renderer : public Component
		{
		public:
			Renderer(Entity& entity, Material material, Mesh mesh);

			Mesh GetMesh() const;

			void ActivateMaterial();

		private:
			Material material;
			Mesh mesh;
		};
	}
}