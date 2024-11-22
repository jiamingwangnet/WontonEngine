#pragma once

#include <WontonEngine/Component.h>
#include <WontonEngine/Components/Transform.h>
#include <WontonEngine/Time.h>
#include <WontonEngine/Input.h>
#include <WontonEngine/Math/Random.h>

class KMBox;

class Spin : public won::Component
{
public:
	Spin(won::Entity entity, won::Game* game, float amount)
		: won::Component{entity, game}, amount{ amount }
	{}

	Spin() = default;

	static void Init(Spin& self) {};

	static void RUpdate(Spin& self) {
		won::cmp::Transform* transf = self.entity.GetComponent<won::cmp::Transform>();
		transf->Rotate(won::Vector3{ 1.0f, 1.0f, 1.0f } *self.amount * won::Time::RDeltaTime());
	};

	static void OnDestroy(Spin& self)
	{
		std::cout << "Entity [" << self.entity.GetId() << "]'s component [Spin] has been destroyed!\n";
	}

	static void Update(Spin& self)
	{
		if (won::Input::GetMouseDown(won::MouseButton::Button_Middle))
		{
			if (won::Random::RandomRange<int>(0, 1))
			{
				won::Entity box = self.game->CreateEntity<KMBox>();

				won::cmp::Transform* transform = box.GetComponent<won::cmp::Transform>();
				transform->Scale(won::Vector3{ won::Random::RandomRange<float>(0.5f, 5.0f), won::Random::RandomRange<float>(0.5f, 5.0f), won::Random::RandomRange<float>(0.5f, 5.0f) });
				transform->Rotate(won::Vector3{ won::Random::RandomRange<float>(0.0f, 360.0f), won::Random::RandomRange<float>(0.0f, 360.0f), won::Random::RandomRange<float>(0.0f, 360.0f) });
				transform->SetLocalPosition(won::Vector3{ won::Random::RandomRange<float>(-80.0f, 80.0f), won::Random::RandomRange<float>(-40.0f, 40.0f), won::Random::RandomRange<float>(-80.0f, 80.0f) });
			}
			else
			{
				self.game->DestroyEntity(self.entity);
			}
		}
	}

private:
	float amount;
};