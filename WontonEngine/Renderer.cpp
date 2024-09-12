#include "include/WontonEngine/Components/Renderer.h"
#include "include/WontonEngine/Game.h"

won::cmp::Renderer::Renderer(Entity entity, Game* game, Material material, Mesh mesh)
	: Component{entity, game}
{
	using namespace won::priv;

	renderer = &(game->GetRenderer());
	if (!renderer->HasRenderable(entity)) renderer->CreateRenderable(entity);

	Renderable* renderable = renderer->RetrieveRenderable(entity);

	renderable->mesh = mesh;
	renderable->material = material;
}

won::Mesh won::cmp::Renderer::GetMesh() const
{
	return renderer->RetrieveRenderable(entity)->mesh;
}

won::Material won::cmp::Renderer::GetMaterial() const
{
	return renderer->RetrieveRenderable(entity)->material;
}

void won::cmp::Renderer::ActivateMaterial()
{
	renderer->RetrieveRenderable(entity)->material->Activate();
}
