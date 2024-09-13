#include "include/WontonEngine/Components/Transform.h"
#include "include/WontonEngine/Game.h"

const won::Vector3 won::cmp::Transform::UP{ 0.0f, 1.0f, 0.0f };
const won::Vector3 won::cmp::Transform::FORWARD{ 0.0f, 0.0f, -1.0f };
const won::Vector3 won::cmp::Transform::RIGHT{ 1.0f, 0.0f, 0.0f };

won::cmp::Transform::Transform(Entity entity, Game* game, Vector3 position, Vector3 scale, Vector3 rotation)
	: Component{ entity, game }
{
	using namespace won::priv;

	renderer = &(game->GetRenderer());
	if (!renderer->HasRenderable(entity)) renderer->CreateRenderable(entity);

	Renderable* renderable = renderer->RetrieveRenderable(entity);
	renderable->position = position;
	renderable->scale = scale;
	renderable->rotation = glm::quat{ glm::vec3{glm::radians(rotation.x()), glm::radians(rotation.y()), glm::radians(rotation.z())} };
}

won::cmp::Transform& won::cmp::Transform::Translate(Vector3 translation)
{
	renderer->RetrieveRenderable(entity)->position += translation;
	return *this;
}

won::cmp::Transform& won::cmp::Transform::Scale(Vector3 scale)
{
	renderer->RetrieveRenderable(entity)->scale *= scale;
	return *this;
}

won::cmp::Transform& won::cmp::Transform::Rotate(Vector3 rotation)
{
	renderer->RetrieveRenderable(entity)->rotation *= glm::quat{ glm::quat{ glm::radians((glm::vec3)rotation) } };
	return *this;
}

won::cmp::Transform& won::cmp::Transform::SetPosition(Vector3 position)
{
	renderer->RetrieveRenderable(entity)->position = position;
	return *this;
}

won::cmp::Transform& won::cmp::Transform::SetScale(Vector3 scale)
{
	renderer->RetrieveRenderable(entity)->scale = scale;
	return *this;
}

won::cmp::Transform& won::cmp::Transform::SetRotation(Vector3 eulerAngles)
{
	renderer->RetrieveRenderable(entity)->rotation = glm::quat{ glm::radians((glm::vec3)eulerAngles) };
	return *this;
}

const won::Vector3& won::cmp::Transform::GetPosition() const
{
	return renderer->RetrieveRenderable(entity)->position;
}

const won::Vector3& won::cmp::Transform::GetScale() const
{
	return renderer->RetrieveRenderable(entity)->scale;
}

const won::Vector3& won::cmp::Transform::GetRotation() const
{
	return glm::eulerAngles(renderer->RetrieveRenderable(entity)->rotation);
}

won::cmp::Transform& won::cmp::Transform::SetParent(Transform* transform)
{
	renderer->RetrieveRenderable(entity)->parent = transform->entity;
	return *this;
}

won::Vector3 won::cmp::Transform::Up() const
{
	return glm::normalize(glm::cross((glm::vec3)Right(), (glm::vec3)Forward()));
}

won::Vector3 won::cmp::Transform::Forward() const
{
	Vector4 dir{ 0.0f, 0.0f, -1.0f, 1.0f };

	dir = glm::mat4_cast(renderer->RetrieveRenderable(entity)->rotation) * (glm::vec4)dir;

	return Vector3{dir.x(), dir.y(), dir.z()}.Normalized();
}

won::Vector3 won::cmp::Transform::Right() const
{
	return glm::normalize(glm::cross((glm::vec3)Forward(), (glm::vec3)UP));
}



won::Matrix4x4 won::cmp::Transform::CalculateMatrix() const
{
	Matrix4x4 model{ 1.0f };

	model = glm::translate((glm::mat4)model, (glm::vec3)renderer->RetrieveRenderable(entity)->position);
	model *= glm::mat4_cast(renderer->RetrieveRenderable(entity)->rotation);
	model = glm::scale((glm::mat4)model, (glm::vec3)renderer->RetrieveRenderable(entity)->scale);

	Entity parent = renderer->RetrieveRenderable(entity)->parent.GetId();

	if (renderer->RetrieveRenderable(entity)->parent.GetId() != INVALID_ENTITY)
		model = parent.GetComponent<Transform>()->CalculateMatrix() * model;

	return model;
}

won::Matrix4x4 won::cmp::Transform::CalculateMatrix(Vector3 scale, Vector3 position, glm::quat rotation)
{
	Matrix4x4 model{ 1.0f };

	model = glm::translate((glm::mat4)model, (glm::vec3)position);
	model *= glm::mat4_cast(rotation);
	model = glm::scale((glm::mat4)model, (glm::vec3)scale);

	return model;
}
