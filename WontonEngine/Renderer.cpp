#include "include/WontonEngine/Components/Renderer.h"

won::cmp::Renderer::Renderer(Entity& entity, Material material, Mesh mesh)
	: Component{entity}, material{material}, mesh{mesh}
{}

won::Mesh won::cmp::Renderer::GetMesh() const
{
	return mesh;
}

won::Material won::cmp::Renderer::GetMaterial() const
{
	return material;
}

void won::cmp::Renderer::ActivateMaterial()
{
	material->Activate();
}
