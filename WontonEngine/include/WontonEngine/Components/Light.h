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
			Light(Entity entity, Game* game, LightType type, Color color, float ambientStr, float intensity);
			Light() = default;

			void SetColor(Color color);

			void SetAmbientStrength(float strength);
			void SetIntensity(float intensity);

			void SetPointLinear(float linear);
			void SetPointQuadratic(float quadratic);

			void SetCutOff(float cutOff);
			void SetOuterCutOff(float outerCutOff);

			static void Init(Light& self) {};
			static void Update(Light& self) {}; // transform parent updates should be done after everything updates
			static void RUpdate(Light& self) {};

		private:
			priv::ScreenRenderer* renderer;
		};
	}
}