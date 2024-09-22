#pragma once

#include <WontonEngine/Scene.h>
#include <WontonEngine/Game.h>
#include <WontonEngine/Components/Transform.h>
#include "MyCamera.h"
#include "Floor.h"
#include "KMBox.h"
#include <WontonEngine/Components/Light.h>

class KMScene : public won::Scene
{
public:
	void Init(won::Game& game) override
	{
		using namespace won;
		using namespace won::cmp;

		Entity camera = game.CreateEntity<MyCamera>();
		game.SetActiveCamera(camera);
		camera.GetComponent<Transform>()->SetLocalPosition({ 0.0f, 5.0f, 5.0f });

		Entity floor = game.CreateEntity<Floor>();
		floor.GetComponent<Transform>()->SetLocalPosition({ .0f, .0f, .0f })
			.SetLocalScale({2000.0f, 1.0f, 2000.0f});

		Entity kmBox = game.CreateEntity<KMBox>();
		kmBox.GetComponent<Transform>()->SetLocalPosition({ 0.0f, 3.0f, 0.0f }).SetLocalScale({3.0f, 3.0f, 3.0f});

		game.CreateEntity<KMBox>().GetComponent<Transform>()->SetLocalPosition({ 2.0f, 1.0f, -3.0f });

		Entity spotLight = game.CreateEntity<Defaults::SpotLight>();
		spotLight.GetComponent<Transform>()->SetLocalPosition({ 0.0f, 15.0f, 0.0f }).SetLocalRotation({ -90.0f, 0.0f, 0.0f });
		Light* cmpSpotLight = spotLight.GetComponent<Light>();
		cmpSpotLight->SetColor({ 190, 190, 190 });
		cmpSpotLight->SetCutOff(10.0f);
		cmpSpotLight->SetOuterCutOff(30.0f);
		cmpSpotLight->SetAmbientStrength(0.0f);

		Entity dirLight = game.CreateEntity<Defaults::DirectionalLight>();
		dirLight.GetComponent<Transform>()->SetLocalRotation({ 35.0f, 0.0f, 0.0f });
		Light* cmpDirLight = dirLight.GetComponent<Light>();
		cmpDirLight->SetColor({ 150, 150, 150, 255 });
		cmpDirLight->SetAmbientStrength(0.1f);
	}
};