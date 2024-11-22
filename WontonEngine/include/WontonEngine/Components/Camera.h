#pragma once

#include "../Component.h"
#include "../Math/Rect.h"
#include "../Math/Matrix.h"
#include "../Rendering/Material.h"

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
			Camera(Entity entity, Game* game, float near, float far, float fov, bool autoCalcAspect = true, float aspect = 0.0);
			Camera(Entity entity, Game* game, float near, float far, Rect viewRect);

			Camera() = default;

			static void Init(Camera& self) {};
			static void Update(Camera& self);
			static void RUpdate(Camera& self) {};
			static void OnDestroy(Camera& self) {};

			ProjectionType GetProjectionType() const;

			Matrix4x4 CalculateLookAt();
			Matrix4x4 CalculateProjection();

			void SetFOV(float fov);
			void SetAspectRatio(float aspect);

			bool WillAutoCalcAspect() const;

			void UsePost(bool v);
			bool IsUsingPost() const;
			void SetPostMaterial(Material material);
			Material GetPostMaterial() const;
		private:
			Matrix4x4 ReturnProjection();

		private:
			ProjectionType projType;

			float near;
			float far;
			float fov;
			float aspect;
			Rect viewRect;
			Matrix4x4 lookat{1.0f};

			Matrix4x4 projection{ 1.0f };

			bool usePost = false;
			Material postMaterial = nullptr;
			bool autoCalcAspect;
		};
	}
}