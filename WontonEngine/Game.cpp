#include "include/WontonEngine/Game.h"
#include "include/WontonEngine/Components/Camera.h"
#include "include/WontonEngine/Input.h"

won::Game::Game(int width, int height, const std::string& name, WinFlags flags, Color clear, preload_func preload, const std::vector<Scene*> scenes, bool vsync)
	: window{width, height, name, flags, clear, vsync}, preload{preload}, scenes{scenes}
{

}

void won::Game::Start()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window.Init();

	preload(*this);

	renderThread = std::thread{ &Game::Render, this };

	while (true)
	{
		priv::InputUpd::InputPoll();

		if (Input::HasQuit()) break;

		// update entities
	}

	renderThread.join();
}

//void won::Game::SetActiveCamera(Entity* camera)
//{
//	cmp::Camera* cameraCmp = camera->GetComponent<cmp::Camera>();
//
//	if (cameraCmp == nullptr)
//		throw std::exception{ "ERROR: Entity does not contain a Camera component." };
//
//	renderer.SetActiveCamera(cameraCmp);
//}

void won::Game::Render()
{
	while (true)
	{
		if (Input::HasQuit()) break;

		//renderer.Render();

		window.SwapBuffer();
	}
}
