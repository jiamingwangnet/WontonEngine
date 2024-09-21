#include "include/WontonEngine/Components/Light.h"
#include "include/WontonEngine/Components/Transform.h"
#include "include/WontonEngine/Game.h"

won::cmp::Light::Light(Entity entity, Game* game, LightType type, Color color, float ambientStr, float intensity)
	: Component{entity, game}
{
	using namespace won::priv;

	renderer = &(game->GetRenderer());
	if (!renderer->HasLight(entity)) renderer->CreateLight(entity);

	LightInternal* light = renderer->RetrieveLight(entity);
	light->type = type;
	light->color = fColor{ (float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f, intensity };
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

void won::cmp::Light::SetIntensity(float intensity)
{
	priv::LightInternal* light = renderer->RetrieveLight(entity);
	light->color.a = intensity;
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

void won::cmp::Light::SetCutOff(float cutOff)
{
	priv::LightInternal* light = renderer->RetrieveLight(entity);
	light->cutOff = glm::cos(glm::radians(cutOff));
	light->dirty = true;
}

void won::cmp::Light::SetOuterCutOff(float outerCutOff)
{
	priv::LightInternal* light = renderer->RetrieveLight(entity);
	light->outerCutOff = glm::cos(glm::radians(outerCutOff));
	light->dirty = true;
}