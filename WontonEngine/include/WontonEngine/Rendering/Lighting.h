#pragma once

#include "../Math/Vector.h"
#include "../Color.h"

namespace won
{
	enum class LightType // maintain order
	{
		Directional = 0,
		Point = 1,
		Spot = 2,
	};

	namespace priv
	{
		struct LightInternal
		{
			LightType type;

			Vector3 position;
			Vector3 direction; // Transform::FORWARD vector rotated by the transform rotation

			Color ambient;
			Color diffuse;
			Color specular;

			float smoothness; // TODO: extract to material uniform

			float linear;
			float quadratic;
		};
	}
}