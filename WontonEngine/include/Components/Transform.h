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
			Transform(Entity& entity);

			void Init() override {};
			void Update() override {};
			void Render() override {};

			void Translate(Vector3 translation);
			void Scale(Vector3 scale);
			void Rotate(Vector3 rotation);

			void SetPosition(Vector3 position);
			void SetScale(Vector3 scale);
			void SetRotation(Vector3 eulerAngles);

			const Vector3& GetPosition() const;
			const Vector3& GetScale() const;
			const Vector3& GetRotation() const;

			Matrix4x4 CalculateMatrix() const;

		private:
			Vector3 scale;
			Vector3 translation;
			Vector3 rotation;
		};
	}
}