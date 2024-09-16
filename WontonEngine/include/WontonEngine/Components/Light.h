#pragma once

#include "../Component.h"
#include "../Rendering/Lighting.h"
#include "../Rendering/ScreenRenderer.h"

namespace won
{
	namespace cmp
	{
		class Light : Component
		{
		public:
			Light(Entity entity, Game* game, LightType type, Color color, float ambientStr);
			Light() = default;

			void SetColor(Color color);

			void SetAmbientStrength(float strength);

			void SetPointLinear(float linear);
			void SetPointQuadratic(float quadratic);

			static void Init(Light& self) {};
			static void Update(Light& self);

		private:
			priv::ScreenRenderer* renderer;
		};
	}
}