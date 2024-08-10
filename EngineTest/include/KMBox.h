#pragma once

#include <WontonEngine/EntityCreator.h>
#include <WontonEngine/Components/Transform.h>
#include <WontonEngine/Components/Camera.h>
#include <WontonEngine/Components/Renderer.h>
#include <WontonEngine/Rendering/Mesh.h>
#include "Spin.h"

class KMBox : public won::EntityCreator
{
private:
	friend class won::Game;

	void Create(won::Entity& entity) const override
	{
		using namespace won;

		entity.AddComponent<cmp::Transform>(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 1.0f, 1.0f, 1.0f }, Vector3{ 0.0f, 0.0f, 0.0f });
		entity.AddComponent<cmp::Renderer>(MaterialManager::GetMaterial("km"), MeshManager::GetMesh(Defaults::BOX_MESH_NAME));
		entity.AddComponent<Spin>(100.0f);
	}
};