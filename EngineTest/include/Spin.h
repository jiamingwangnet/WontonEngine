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

	void Init() override {};
	void Update() override
	{
		won::cmp::Transform* transf = entity.GetComponent<won::cmp::Transform>();
		transf->Rotate(won::Vector3{ 1.0f, 1.0f, 1.0f } * amount * won::Time::DeltaTime());
	}

private:
	float amount;
};