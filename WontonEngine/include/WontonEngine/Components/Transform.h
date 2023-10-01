#pragma once

#include "../Component.h"
#include "../Math/Vector.h"
#include "../Math/Matrix.h"

namespace won
{
	namespace cmp
	{
		class Transform : public Component
		{
		public:
			Transform(Entity& entity, Vector3 position, Vector3 scale, Vector3 rotation);

			void Init() override {};
			void Update() override {};

			void Translate(Vector3 translation);
			void Scale(Vector3 scale);
			void Rotate(Vector3 rotation); // degrees

			void SetPosition(Vector3 position);
			void SetScale(Vector3 scale);
			void SetRotation(Vector3 eulerAngles);

			const Vector3& GetPosition() const;
			const Vector3& GetScale() const;
			const Vector3& GetRotation() const; // returns in radians

			Vector3 Up() const;
			Vector3 Forward() const;
			Vector3 Right() const;

			Matrix4x4 CalculateMatrix() const;

		public:
			static const Vector3 UP;
			static const Vector3 FORWARD;
			static const Vector3 RIGHT;

		private:
			Vector3 scale;
			Vector3 position;
			Vector3 rotation;
		};
	}
}