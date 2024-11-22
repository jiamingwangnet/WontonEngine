#pragma once

#include "../Component.h"
#include "../Rendering/Material.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Renderable.h"
#include "../Rendering/ScreenRenderer.h"

namespace won
{
	namespace cmp
	{
		class Renderer : public Component
		{
		public:
			Renderer(Entity entity, Game* game, Material material, Mesh mesh);

			Renderer() = default;

			static void Init(Renderer& self) {};
			static void Update(Renderer& self) {};
			static void RUpdate(Renderer& self) {};
			static void OnDestroy(Renderer& self) {};

			Mesh GetMesh() const;
			Material GetMaterial() const;

			void ActivateMaterial();

		private:
			priv::ScreenRenderer* renderer = nullptr;
		};
	}
}