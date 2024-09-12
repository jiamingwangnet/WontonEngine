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

			Vector3 scale;
			Vector3 position;
			glm::quat rotation;
		};
	}
}