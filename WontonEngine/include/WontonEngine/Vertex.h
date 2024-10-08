#pragma once

#include "Math/Vector.h"
#include "Color.h"

namespace won
{
	struct Vertex
	{
		Vector3 position;
		Vector2 uv;
		Vector3 normal;
	};
}