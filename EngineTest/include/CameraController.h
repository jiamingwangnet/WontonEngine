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
	CameraController(won::Entity entity, won::Game* game)
		: won::Component{entity, game}
	{}

	CameraController() = default;

	static void Init(CameraController& self)
	{

	}

	static void Update(CameraController& self)
	{
		won::cmp::Transform* transform = self.entity.GetComponent<won::cmp::Transform>();

		if (won::Input::GetKey(won::KeyCode::Key_W))
		{
			transform->SetLocalPosition(transform->GetLocalPosition() + transform->Forward() * self.speed * won::Time::DeltaTime());
		}
		if (won::Input::GetKey(won::KeyCode::Key_S))
		{
			transform->SetLocalPosition(transform->GetLocalPosition() + transform->Forward() * -self.speed * won::Time::DeltaTime());
		}
		if (won::Input::GetKey(won::KeyCode::Key_A))
		{
			transform->SetLocalPosition(transform->GetLocalPosition() + transform->Right() * -self.speed * won::Time::DeltaTime());
		}
		if (won::Input::GetKey(won::KeyCode::Key_D))
		{
			transform->SetLocalPosition(transform->GetLocalPosition() + transform->Right() * self.speed * won::Time::DeltaTime());
		}

		if (won::Input::GetMouse(won::MouseButton::Button_Right))
		{
			won::Vector2 movement = won::Input::GetMouseMovement();

			movement *= self.sens;
			movement.y() *= -1.0f;

			self.yRot -= movement.x();
			self.xRot += movement.y();

			self.xRot = self.xRot > 89.0f ? 89.0f : self.xRot;
			self.xRot = self.xRot < -89.0f ? -89.0f : self.xRot;

			transform->SetLocalRotation({ self.xRot, self.yRot, 0.0f });
		}

		if (won::Input::GetKeyDown(won::KeyCode::Key_P))
		{
			if (self.game->GetCurrentScene() == 0) self.game->LoadScene(1);
			else if (self.game->GetCurrentScene() == 1) self.game->LoadScene(0);
		}
	}

private:
	float speed = 70.0f;
	float xRot = 0.0f;
	float yRot = -90.0f;
	float sens = 0.2f;
};