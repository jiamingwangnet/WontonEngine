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
			Light(Entity entity, Game* game, LightType type, Color ambient, Color diffuse, Color specular, float ambientStr, float diffuseStr, float specularStr);
			Light() = default;

			void SetAmbientColor(Color ambient);
			void SetDiffuseColor(Color diffuse);
			void SetSpecularColor(Color specular);

			void SetAmbientStrength(float strength);
			void SetDiffuseStrength(float strength);
			void SetSpecularStrength(float strength);

			void SetPointLinear(float linear);
			void SetPointQuadratic(float quadratic);

			static void Init(Light& self) {};
			static void Update(Light& self);

		private:
			priv::ScreenRenderer* renderer;
		};
	}
}