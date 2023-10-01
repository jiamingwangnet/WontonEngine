#pragma once

#include <WontonEngine/Scene.h>
#include <WontonEngine/Game.h>
#include <WontonEngine/Defaults.h>
#include <WontonEngine/Entity.h>
#include "MyCamera.h"

class MainScene : public won::Scene
{
public:
	void Init(won::Game& game) override
	{
		won::Entity* box = game.CreateEntity<won::Defaults::Box>();
		won::cmp::Transform* transform = box->GetComponent<won::cmp::Transform>();
		//transform->Scale(won::Vector3{ 10.0f, 10.0f, 10.0f });
		transform->Rotate(won::Vector3{ 45.0f, 45.0f, 45.0f });

		won::Entity* camera = game.CreateEntity<MyCamera>();

		game.SetActiveCamera(camera);
	}
};