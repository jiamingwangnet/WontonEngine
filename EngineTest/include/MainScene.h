#pragma once

#include <WontonEngine/Scene.h>
#include <WontonEngine/Game.h>
#include <WontonEngine/Defaults.h>
#include <WontonEngine/Entity.h>
#include <WontonEngine/Math/Random.h>
#include "MyCamera.h"
#include "KMBox.h"
#include "Floor.h"
#include <WontonEngine/Components/Light.h>

class MainScene : public won::Scene
{
public:
	void Init(won::Game& game) override
	{
		won::Entity floor = game.CreateEntity<Floor>();

		for (int i = 0; i < 800; i++)
		{
			won::Entity box;

			if (won::Random::RandomRange<int>(0, 5) == 1)
			{
				box = game.CreateEntity<won::Defaults::Box>();
			}
			else
			{
				box = game.CreateEntity<KMBox>();
			}

			//box = game.CreateEntity<KMBox>();

			won::cmp::Transform* transform = box.GetComponent<won::cmp::Transform>();
			transform->Scale(won::Vector3{ won::Random::RandomRange<float>(0.5f, 5.0f), won::Random::RandomRange<float>(0.5f, 5.0f), won::Random::RandomRange<float>(0.5f, 5.0f) });
			transform->Rotate(won::Vector3{ won::Random::RandomRange<float>(0.0f, 360.0f), won::Random::RandomRange<float>(0.0f, 360.0f), won::Random::RandomRange<float>(0.0f, 360.0f) });
			transform->SetLocalPosition(won::Vector3{ won::Random::RandomRange<float>(-80.0f, 80.0f), won::Random::RandomRange<float>(-40.0f, 40.0f), won::Random::RandomRange<float>(-80.0f, 80.0f) });
		}

		won::Entity camera = game.CreateEntity<MyCamera>();
		won::Entity cameraLight = game.CreateEntity<won::Defaults::SpotLight>();
		won::cmp::Light* cml = cameraLight.GetComponent<won::cmp::Light>();
		cameraLight.GetComponent<won::cmp::Transform>()->SetParent(camera.GetComponent<won::cmp::Transform>()).SetLocalRotation({ 0.0f, 0.0f, 0.0f });

		/*won::Entity testlBox = game.CreateEntity<won::Defaults::Box>();
		testlBox.GetComponent<won::cmp::Transform>()->SetParent(camera.GetComponent<won::cmp::Transform>()).SetLocalPosition({ 0.0f, 0.0f,-2.0f });*/

		game.SetActiveCamera(camera);

		won::Entity testBox = game.CreateEntity<KMBox>();
		won::cmp::Transform* testBoxTra = testBox.GetComponent<won::cmp::Transform>();

		testBoxTra->SetLocalPosition(won::Vector3{230.0f, 0.0f, 0.0f });
		testBoxTra->Scale(won::Vector3{ 5.0f, 5.0f, 5.0f });

		won::Entity testBox2 = game.CreateEntity<KMBox>();
		won::cmp::Transform* testBoxTra2 = testBox2.GetComponent<won::cmp::Transform>();
		testBoxTra->SetLocalScale(won::Vector3{ 5.0f, 5.0f, 5.0f });

		testBoxTra2->SetParent(testBoxTra);
		testBoxTra2->SetPosition(won::Vector3{ 230.0f, 10.0f, 0.0f });

		for (int i = 0; i < 64; i++)
		{
			won::Entity light = game.CreateEntity<won::Defaults::PointLight>();
			light.GetComponent<won::cmp::Transform>()->SetLocalPosition(won::Vector3{ won::Random::RandomRange<float>(-80.0f, 80.0f), won::Random::RandomRange<float>(0.0f, 40.0f), won::Random::RandomRange<float>(-80.0f, 80.0f) });
			won::cmp::Light* lightcmp = light.GetComponent<won::cmp::Light>();
			lightcmp->SetColor({ 90, 90, 90, 0xff });
			lightcmp->SetPointLinear(0.045f);
			lightcmp->SetPointQuadratic(0.0075f);
			lightcmp->SetAmbientStrength(0.0f);
		}

		won::Entity light = game.CreateEntity<won::Defaults::SpotLight>();
		light.GetComponent<won::cmp::Transform>()->SetLocalPosition({ 0.0f, 10.0f, 0.0f });
		light.GetComponent<won::cmp::Transform>()->SetLocalRotation({ -90.0f, 0.0f, 0.0f });
		won::cmp::Light* lightcmp = light.GetComponent<won::cmp::Light>();
		lightcmp->SetColor({ 120, 120, 120, 0xff });
		lightcmp->SetPointLinear(0.09f);
		lightcmp->SetPointQuadratic(0.032f);
		//lightcmp->SetAmbientStrength(0.05f);

		won::Entity light2 = game.CreateEntity<won::Defaults::PointLight>();
		light2.GetComponent<won::cmp::Transform>()->SetLocalPosition({ 0.0f, 1.0f, 0.0f });
		won::cmp::Light* light2cmp = light2.GetComponent<won::cmp::Light>();
		light2cmp->SetPointLinear(0.09f);
		light2cmp->SetPointQuadratic(0.032f);
		light2cmp->SetColor({ 255, 255, 255, 0xff });
		light2cmp->SetIntensity(10.0f);

		won::Entity dirlight = game.CreateEntity<won::Defaults::DirectionalLight>();
		dirlight.GetComponent<won::cmp::Transform>()->SetLocalRotation({45.0f, 0.0f, 0.0f});
		won::cmp::Light* dirLightl = dirlight.GetComponent<won::cmp::Light>();
		dirLightl->SetColor({ 60, 60, 60 });
		dirLightl->SetAmbientStrength(0.0f);
	}
};