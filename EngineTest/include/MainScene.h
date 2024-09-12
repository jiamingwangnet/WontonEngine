#pragma once

#include <WontonEngine/Scene.h>
#include <WontonEngine/Game.h>
#include <WontonEngine/Defaults.h>
#include <WontonEngine/Entity.h>
#include <WontonEngine/Math/Random.h>
#include "MyCamera.h"
#include "KMBox.h"
#include "Floor.h"

class MainScene : public won::Scene
{
public:
	void Init(won::Game& game) override
	{
		won::Entity floor = game.CreateEntity<Floor>();

		for (int i = 0; i < 5000; i++)
		{
			won::Entity box;

			/*if (won::Random::RandomRange<int>(0, 1) == 1)
			{
				box = game.CreateEntity<KMBox>();
			}
			else
			{
				box = game.CreateEntity<won::Defaults::Box>();
			}*/

			box = game.CreateEntity<KMBox>();

			won::cmp::Transform* transform = box.GetComponent<won::cmp::Transform>();
			transform->Scale(won::Vector3{ won::Random::RandomRange<float>(0.5f, 5.0f), won::Random::RandomRange<float>(0.5f, 5.0f), won::Random::RandomRange<float>(0.5f, 5.0f) });
			transform->Rotate(won::Vector3{ won::Random::RandomRange<float>(0.0f, 360.0f), won::Random::RandomRange<float>(0.0f, 360.0f), won::Random::RandomRange<float>(0.0f, 360.0f) });
			transform->SetPosition(won::Vector3{ won::Random::RandomRange<float>(-80.0f, 80.0f), won::Random::RandomRange<float>(-80.0f, 80.0f), won::Random::RandomRange<float>(-80.0f, 80.0f) });
		}

		won::Entity camera = game.CreateEntity<MyCamera>();

		game.SetActiveCamera(camera);

		won::Entity testBox = game.CreateEntity<KMBox>();
		won::cmp::Transform* testBoxTra = testBox.GetComponent<won::cmp::Transform>();

		testBoxTra->Scale(won::Vector3{ 2.0f, 2.0f, 2.0f });
	}
};