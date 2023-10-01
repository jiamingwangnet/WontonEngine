#pragma once

#include "Math/Vector.h"
#include "Color.h"

namespace won
{
	struct Vertex
	{
		Vector3 position;
		Vector2 uv;

		Color color;
	};

	/*struct Vertex
	{
		struct Vec3 
		{
			float x;
			float y;
			float z;
		} position;
		struct Vec2
		{
			float u;
			float v;
		} uv;

		Color color;
	};*/
}