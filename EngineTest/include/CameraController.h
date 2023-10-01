#pragma once

#include <WontonEngine/Component.h>
#include <WontonEngine/Input.h>
#include <WontonEngine/Components/Transform.h>
#include <WontonEngine/Math/Vector.h>
#include <WontonEngine/Entity.h>
#include <WontonEngine/Time.h>
#include <iostream>

class CameraController : public won::Component
{
public:
	CameraController(won::Entity& entity)
		: won::Component{entity}
	{}

	void Init() override
	{

	}

	void Update() override
	{
		won::cmp::Transform* transform = entity.GetComponent<won::cmp::Transform>();

		if (won::Input::GetKey(won::KeyCode::Key_W))
		{
			transform->SetPosition(transform->GetPosition() + transform->Forward() * speed * won::Time::DeltaTime());
		}
		if (won::Input::GetKey(won::KeyCode::Key_S))
		{
			transform->SetPosition(transform->GetPosition() + transform->Forward() * -speed * won::Time::DeltaTime());
		}
		if (won::Input::GetKey(won::KeyCode::Key_A))
		{
			transform->SetPosition(transform->GetPosition() + transform->Right() * -speed * won::Time::DeltaTime());
		}
		if (won::Input::GetKey(won::KeyCode::Key_D))
		{
			transform->SetPosition(transform->GetPosition() + transform->Right() * speed * won::Time::DeltaTime());
		}

		if (won::Input::GetMouse(won::MouseButton::Button_Right))
		{
			won::Vector2 movement = won::Input::GetMouseMovement();

			movement *= sens;
			movement.y() *= -1.0f;

			yRot += movement.x();
			xRot += movement.y();

			xRot = xRot > 89.0f ? 89.0f : xRot;
			xRot = xRot < -89.0f ? -89.0f : xRot;

			transform->SetRotation({ xRot, yRot, 0.0f });
		}
	}

private:
	float speed = 70.0f;
	float xRot = 0.0f;
	float yRot = -90.0f;
	float sens = 0.2f;
};