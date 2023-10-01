#include "include/WontonEngine/Components/Camera.h"
#include "include/WontonEngine/Components/Transform.h"
#include "include/WontonEngine/Entity.h"

won::cmp::Camera::Camera(Entity& entity, float near, float far, float fov, float aspect)
	: Component{ entity }, near{ near }, far{ far }, fov{ fov }, aspect{ aspect }, projType{ ProjectionType::Perspective }, viewRect{ {0.0f, 0.0f}, 0.0f, 0.0f }
{}

won::cmp::Camera::Camera(Entity& entity, float near, float far, Rect viewRect)
	: Component{entity}, near{ near }, far{ far }, viewRect{viewRect}, projType{ ProjectionType::Perspective }, aspect{0.0}, fov{0.0}
{}

won::cmp::Camera::ProjectionType won::cmp::Camera::GetProjectionType() const
{
	return projType;
}

won::Matrix4x4 won::cmp::Camera::CalculateLookAt()
{
	Transform* transform = entity.GetComponent<Transform>();
	Vector3 position{ 0.0f, 0.0f, 0.0f };
	Vector3 forwards = cmp::Transform::FORWARD;
	Vector3 upwards = cmp::Transform::UP;

	if (transform != nullptr)
	{
		position = transform->GetPosition();
		forwards = transform->Forward();
	}

	return Matrix4x4{glm::lookAt((glm::vec3)position, (glm::vec3)(position + forwards), (glm::vec3)upwards)};
}

won::Matrix4x4 won::cmp::Camera::CalculateProjection()
{
	switch (projType)
	{
	case ProjectionType::Orthographic:
		return Matrix4x4{
			glm::ortho(viewRect.position.x(),
			viewRect.position.x() + viewRect.width,
			viewRect.position.y() + viewRect.height,
			viewRect.position.y(), near, far)
		};
	case ProjectionType::Perspective:
		return Matrix4x4{ glm::perspective(glm::radians(fov), aspect, near, far)};
	}

	return Matrix4x4{ 1.0f };
}
