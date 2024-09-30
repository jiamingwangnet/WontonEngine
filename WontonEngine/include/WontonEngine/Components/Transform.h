#pragma once

#include "../Component.h"
#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Rendering/Renderable.h"
#include "../Rendering/ScreenRenderer.h"

namespace won
{
	namespace cmp
	{
		class Transform : public Component
		{
		public:
			Transform(Entity entity, Game* game, Vector3 position, Vector3 scale, Vector3 rotation);

			Transform() = default;

			static void Init(Transform& self) {};
			static void Update(Transform& self) {};
			static void RUpdate(Transform& self) {};

			Transform& Translate(Vector3 translation);
			Transform& Scale(Vector3 scale);
			Transform& Rotate(Vector3 rotation); // degrees

			Transform& SetLocalPosition(Vector3 position);
			Transform& SetLocalScale(Vector3 scale);
			Transform& SetLocalRotation(Vector3 eulerAngles);

			const Vector3 GetLocalPosition() const;
			const Vector3 GetLocalScale() const;
			const Vector3 GetLocalRotation() const; // returns in radians

			// global
			const Vector3 GetPosition() const;
			const Vector3 GetScale() const;
			const Vector3 GetRotation() const;

			const glm::quat GetRotationQuat() const;

			// TODO: encapsulate quaternion
			const glm::quat GetLocalRotationQuat() const;

			Transform& SetParent(Transform* transform);

			Vector3 Up() const;
			Vector3 Forward() const;
			Vector3 Right() const;

			Matrix4x4 CalculateMatrix() const;

			// wont work if transform updates after than the calling component


			// TODO: add wrapper class for glm::quat
			static Matrix4x4 CalculateMatrix(const Vector3& scale, const Vector3& position, const glm::quat& rotation);

		public:
			static const Vector3 UP;
			static const Vector3 FORWARD;
			static const Vector3 RIGHT;

		private:
			priv::ScreenRenderer* renderer = nullptr;
		};
	}
}