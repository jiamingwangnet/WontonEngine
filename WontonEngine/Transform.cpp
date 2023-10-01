#include "include/WontonEngine/Components/Transform.h"

const won::Vector3 won::cmp::Transform::UP{ 0.0f, 1.0f, 0.0f };
const won::Vector3 won::cmp::Transform::FORWARD{ 0.0f, 0.0f, -1.0f };
const won::Vector3 won::cmp::Transform::RIGHT{ 1.0f, 0.0f, 0.0f };

won::cmp::Transform::Transform(Entity& entity, Vector3 position, Vector3 scale, Vector3 rotation)
	: Component{ entity }, position{ position }, scale{ scale }, rotation{ Vector3{glm::radians(rotation.x()), glm::radians(rotation.y()), glm::radians(rotation.z())} }
{}

void won::cmp::Transform::Translate(Vector3 translation)
{
	position += translation;
}

void won::cmp::Transform::Scale(Vector3 scale)
{
	this->scale *= scale;
}

void won::cmp::Transform::Rotate(Vector3 rotation)
{
	Vector3 rad{ glm::radians(rotation.x()), glm::radians(rotation.y()), glm::radians(rotation.z())};
	this->rotation += rad;
}

void won::cmp::Transform::SetPosition(Vector3 position)
{
	this->position = position;
}

void won::cmp::Transform::SetScale(Vector3 scale)
{
	this->scale = scale;
}

void won::cmp::Transform::SetRotation(Vector3 eulerAngles)
{
	Vector3 rad{ glm::radians(eulerAngles.x()), glm::radians(eulerAngles.y()) ,glm::radians(eulerAngles.z()) };
	this->rotation = rad;
}

const won::Vector3& won::cmp::Transform::GetPosition() const
{
	return position;
}

const won::Vector3& won::cmp::Transform::GetScale() const
{
	return scale;
}

const won::Vector3& won::cmp::Transform::GetRotation() const
{
	return rotation;
}

won::Vector3 won::cmp::Transform::Up() const
{
	return glm::normalize(glm::cross((glm::vec3)Right(), (glm::vec3)Forward()));
}

won::Vector3 won::cmp::Transform::Forward() const
{
	Vector3 dir{ 0.0f, 0.0f, -1.0f };

	dir.x() = std::cos(rotation.y()) * std::cos(rotation.x());
	dir.y() = std::sin(rotation.x());
	dir.z() = std::sin(rotation.y()) * std::cos(rotation.x());

	return dir.Normalized();
}

won::Vector3 won::cmp::Transform::Right() const
{
	return glm::normalize(glm::cross((glm::vec3)Forward(), (glm::vec3)UP));
}



won::Matrix4x4 won::cmp::Transform::CalculateMatrix() const
{
	Matrix4x4 model{ 1.0f };

	model = glm::translate((glm::mat4)model, (glm::vec3)position);
	model *= glm::mat4_cast(glm::quat{ (glm::vec3)rotation });
	model = glm::scale((glm::mat4)model, (glm::vec3)scale);

	return model;
}
