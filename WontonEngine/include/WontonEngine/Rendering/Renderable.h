#pragma once

#include "Mesh.h"
#include "Material.h"
#include "../Math/Vector.h"

namespace won
{
	namespace priv
	{
		struct Renderable
		{
			Material material = nullptr;
			Mesh mesh = nullptr;

			Vector3 scale{ 1.0f, 1.0f, 1.0f };
			Vector3 position{0.0f, 0.0f, 0.0f};
			glm::quat rotation{0.0f, 0.0f, 0.0f, 1.0f};

			Entity parent = INVALID_ENTITY; // no parent

			bool tdirty = true;
		};
	}
}