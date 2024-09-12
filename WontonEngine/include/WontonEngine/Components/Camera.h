#pragma once

#include "../Component.h"
#include "../Math/Rect.h"
#include "../Math/Matrix.h"

namespace won
{
	namespace cmp
	{
		class Camera : public Component
		{
		public:
			enum class ProjectionType
			{
				Orthographic,
				Perspective
			};
		public:
			Camera(Entity entity, Game* game, float near, float far, float fov, float aspect);
			Camera(Entity entity, Game* game, float near, float far, Rect viewRect);

			Camera() = default;

			static void Init(Camera& self) {};
			static void Update(Camera& self) {};

			ProjectionType GetProjectionType() const;

			Matrix4x4 CalculateLookAt();
			Matrix4x4 CalculateProjection();

		private:
			ProjectionType projType;

			float near;
			float far;
			float fov;
			float aspect;
			Rect viewRect;
		};
	}
}