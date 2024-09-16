#include "include/WontonEngine/Components/Light.h"
#include "include/WontonEngine/Components/Transform.h"
#include "include/WontonEngine/Game.h"

won::cmp::Light::Light(Entity entity, Game* game, LightType type, Color color, float ambientStr)
	: Component{entity, game}
{
	using namespace won::priv;

	renderer = &(game->GetRenderer());
	if (!renderer->HasLight(entity)) renderer->CreateLight(entity);

	LightInternal* light = renderer->RetrieveLight(entity);
	light->type = type;
	light->color = fColor{ (float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f, 1.0f };
	light->ambientStrength = ambientStr;
	
	if (!renderer->HasRenderable(entity)) renderer->CreateRenderable(entity);
}

void won::cmp::Light::SetColor(Color color)
{
	priv::LightInternal* light = renderer->RetrieveLight(entity);
	light->color.r = (float)color.r / 255.0f;
	light->color.g = (float)color.g / 255.0f;
	light->color.b = (float)color.b / 255.0f;
	light->dirty = true;
}

void won::cmp::Light::SetAmbientStrength(float strength)
{
	priv::LightInternal* light = renderer->RetrieveLight(entity);
	light->ambientStrength = strength;
	light->dirty = true;
}

void won::cmp::Light::SetPointLinear(float linear)
{
	priv::LightInternal* light = renderer->RetrieveLight(entity);
	light->linear = linear;
	light->dirty = true;
}

void won::cmp::Light::SetPointQuadratic(float quadratic)
{
	priv::LightInternal* light = renderer->RetrieveLight(entity);
	light->quadratic = quadratic;
	light->dirty = true;
}

void won::cmp::Light::Update(Light& self)
{
	using namespace priv;

	// TODO: optimise componet retrieval away
	Transform* transform = self.entity.GetComponent<Transform>();
	LightInternal* light = self.renderer->RetrieveLight(self.entity);

	// TODO: set to global position
	light->position = transform->GetPosition();
	//std::cout << light->position.x() << ' ' << light->position.y() << ' ' << light->position.z() << '\n';
	glm::vec3 forward = (glm::vec3)Transform::FORWARD;
	light->direction = (Vector3)(glm::vec4{ forward.x, forward.y, forward.z, 1.0f } * glm::mat4_cast(transform->GetLocalRotationQuat()));

	light->dirty |= transform->IsDirty(); // may give broken results if transform updates after light
}
