#pragma once

#include <WontonEngine/Component.h>
#include <WontonEngine/Input.h>
#include "CameraController.h"

// Test Deleting component
class DeleteComponent : public won::Component
{
public:
	DeleteComponent() = default;

	DeleteComponent(won::Entity entity, won::Game* game)
		: won::Component{entity, game}
	{

	}

	static void Init(DeleteComponent& self) {};
	static void Update(DeleteComponent& self ) 
	{
		using namespace won;
		
		if (Input::GetKeyDown(KeyCode::Key_M))
		{
			self.entity.RemoveComponent<CameraController>();
		}

		if (Input::GetKeyDown(KeyCode::Key_N))
		{
			self.entity.AddComponent<CameraController>();
		}
	};
	static void RUpdate(DeleteComponent& self) {};
	static void OnDestroy(DeleteComponent& self) {};
};