#pragma once

#include "../Math/Vector.h"
#include "../Color.h"
#include <cstdint>

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
		// representation in shaders
		// order matters for alignment
		// size must be a multiple of 16
		PACK(struct LightInternalBase
		{
			                         // incremental size         offset         +16
			Vector4 position;        // 16                       0              16
			Vector4 direction;       // 32                       16             32
			fColor color;            // 48						 32             48
			int type;                // 52						 48             64
			float ambientStrength;   // 56						 52             68
			float linear;            // 60						 56             72
			float quadratic;         // 64						 60             76
			float cutOff;            // 68						 64             80
			float outerCutOff;       // 72						 68             84
			char _padding00[8];      // 80                       72             88
		});

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