#include "include/WontonEngine/Components/Light.h"
#include "include/WontonEngine/Components/Transform.h"
#include "include/WontonEngine/Game.h"

won::cmp::Light::Light(Entity entity, Game* game, LightType type, Color ambient, Color diffuse, Color specular, float ambientStr, float diffuseStr, float specularStr)
	: Component{entity, game}
{
	using namespace won::priv;

	renderer = &(game->GetRenderer());
	if (!renderer->HasLight(entity)) renderer->CreateLight(entity);

	LightInternal* light = renderer->RetrieveLight(entity);
	light->type = type;
	light->ambient = fColor{ (float)ambient.r / 255.0f, (float)ambient.g / 255.0f, (float)ambient.b / 255.0f, ambientStr };
	light->diffuse = fColor{ (float)diffuse.r / 255.0f, (float)diffuse.g / 255.0f, (float)diffuse.b / 255.0f, diffuseStr };
	light->specular = fColor{ (float)specular.r / 255.0f, (float)specular.g / 255.0f, (float)specular.b / 255.0f, specularStr };
}

void won::cmp::Light::SetAmbientColor(Color ambient)
{
	priv::LightInternal* light = renderer->RetrieveLight(entity);
	light->ambient.r = (float)ambient.r / 255.0f;
	light->ambient.g = (float)ambient.g / 255.0f;
	light->ambient.b = (float)ambient.b / 255.0f;
}

void won::cmp::Light::SetDiffuseColor(Color diffuse)
{
	priv::LightInternal* light = renderer->RetrieveLight(entity);
	light->diffuse.r = (float)diffuse.r / 255.0f;
	light->diffuse.g = (float)diffuse.g / 255.0f;
	light->diffuse.b = (float)diffuse.b / 255.0f;
}

void won::cmp::Light::SetSpecularColor(Color specular)
{
	priv::LightInternal* light = renderer->RetrieveLight(entity);
	light->specular.r = (float)specular.r / 255.0f;
	light->specular.g = (float)specular.g / 255.0f;
	light->specular.b = (float)specular.b / 255.0f;
}

void won::cmp::Light::SetAmbientStrength(float strength)
{
	renderer->RetrieveLight(entity)->ambient.a = strength;
}

void won::cmp::Light::SetDiffuseStrength(float strength)
{
	renderer->RetrieveLight(entity)->diffuse.a = strength;
}

void won::cmp::Light::SetSpecularStrength(float strength)
{
	renderer->RetrieveLight(entity)->specular.a = strength;
}

void won::cmp::Light::SetPointLinear(float linear)
{
	renderer->RetrieveLight(entity)->linear = linear;
}

void won::cmp::Light::SetPointQuadratic(float quadratic)
{
	renderer->RetrieveLight(entity)->quadratic = quadratic;
}

void won::cmp::Light::Update(Light& self)
{
	using namespace priv;

	// TODO: optimise componet retrieval away
	Transform* transform = self.entity.GetComponent<Transform>();
	LightInternal* light = self.renderer->RetrieveLight(self.entity);

	// TODO: set to global position
	light->position = transform->GetLocalPosition();
	glm::vec3 forward = (glm::vec3)Transform::FORWARD;
	light->direction = (Vector3)(glm::vec4{ forward.x, forward.y, forward.z, 1.0f } * glm::mat4_cast(transform->GetLocalRotationQuat()));
}
