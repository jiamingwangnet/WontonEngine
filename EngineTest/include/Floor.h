#pragma once

#include <WontonEngine/EntityCreator.h>
#include <WontonEngine/Components/Transform.h>
#include <WontonEngine/Components/Renderer.h>
#include <WontonEngine/Rendering/Mesh.h>

// The EntityCreator class is extended to create entity "presets"
class Floor : public won::EntityCreator
{
private:
	friend class won::Game;

	void Create(won::Entity& entity) const override
	{
		using namespace won;

		entity.AddComponent<cmp::Transform>(Vector3{ 0.0f, -20.0f, 0.0f }, Vector3{ 100.0f, 1.0f, 100.0f }, Vector3{ 0.0f, 0.0f, 0.0f });
		entity.AddComponent<cmp::Renderer>(MaterialManager::GetMaterial("Green"), MeshManager::GetMesh(Defaults::PLANE_MESH_NAME));
	}
};