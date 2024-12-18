#pragma once

#include <WontonEngine/EntityCreator.h>
#include <WontonEngine/Components/Transform.h>
#include <WontonEngine/Components/Camera.h>
#include "CameraController.h"

class MyCamera : public won::EntityCreator
{
public:
	void Create(won::Entity& entity) const override
	{
		entity.AddComponent<won::cmp::Transform>(won::Vector3{ 0.0f,0.0f,5.0f }, won::Vector3{ 1.0f,1.0f,1.0f }, won::Vector3{0.0f,-90.0f,0.0f});
		won::cmp::Camera* cam = entity.AddComponent<won::cmp::Camera>(0.1f, 1000.0f, 45.0f);
		cam->UsePost(true);
		cam->SetPostMaterial(won::MaterialManager::GetMaterial("PostProcess"));
		entity.AddComponent<CameraController>();
		entity.AddComponent<DeleteComponent>();
	}
};