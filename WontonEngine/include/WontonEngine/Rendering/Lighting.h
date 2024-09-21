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

			// strength stored in alpha channel
			fColor color;
			float ambientStrength;

			float linear;
			float quadratic;

			float cutOff;
			float outerCutOff;

			// all below are not part of the shader definition
			// set uniform only when dirty is true
			bool dirty = true;
		};
	}
}