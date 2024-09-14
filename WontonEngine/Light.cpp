#include "include/WontonEngine/Components/Light.h"
#include "include/WontonEngine/Components/Transform.h"
#include "include/WontonEngine/Game.h"

won::cmp::Light::Light(Entity entity, Game* game, LightType type, Color ambient, Color diffuse, Color specular, float smoothness)
	: Component{entity, game}
{
	using namespace won::priv;

	renderer = &(game->GetRenderer());
	if (!renderer->HasLight(entity)) renderer->CreateLight(entity);

	LightInternal* light = renderer->RetrieveLight(entity);
	light->type = type;
	light->ambient = ambient;
	light->diffuse = diffuse;
	light->specular = specular;
	light->smoothness = smoothness;
}

void won::cmp::Light::SetAmbientColor(Color ambient)
{
	renderer->RetrieveLight(entity)->ambient = ambient;
}

void won::cmp::Light::SetDiffuseColor(Color diffuse)
{
	renderer->RetrieveLight(entity)->diffuse = diffuse;
}

void won::cmp::Light::SetSpecularColor(Color specular)
{
	renderer->RetrieveLight(entity)->specular = specular;
}

void won::cmp::Light::SetSmoothness(float smoothness)
{
	renderer->RetrieveLight(entity)->smoothness = smoothness;
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
