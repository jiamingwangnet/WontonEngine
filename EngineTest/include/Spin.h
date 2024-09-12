#pragma once

#include <WontonEngine/Component.h>
#include <WontonEngine/Components/Transform.h>
#include <WontonEngine/Time.h>

class Spin : public won::Component
{
public:
	Spin(won::Entity& entity, float amount)
		: won::Component{entity}, amount{ amount }
	{}

	Spin() = default;

	static void Init(Spin& self) {};
	static void Update(Spin& self)
	{
		won::cmp::Transform* transf = self.entity.GetComponent<won::cmp::Transform>();
		transf->Rotate(won::Vector3{ 1.0f, 1.0f, 1.0f } * self.amount * won::Time::DeltaTime());
	}

private:
	float amount;
};