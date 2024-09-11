#include "include/WontonEngine/Game.h"
#include "include/WontonEngine/Components/Camera.h"
#include "include/WontonEngine/Input.h"
#include "include/WontonEngine/Time.h"
#include "include/WontonEngine/Entity.h"
#include <iostream>
#include "include/WontonEngine/UpdateLimiter.h"

won::Game::Game(int width, int height, const std::string& name, WinFlags flags, Color clear, preload_func preload, const std::vector<Scene*> scenes, bool vsync, float targetFramerate, float targetUpdateRate)
	: window{width, height, name, flags, clear, vsync}, preload{preload}, scenes{scenes}, targetFramerate{targetFramerate}, targetUpdateRate{ targetUpdateRate }
{

}

void won::Game::Start()
{
	int err = SDL_Init(SDL_INIT_EVERYTHING);

	if (err != 0)
	{
		Error::ThrowError("SDL initialisation failed!", std::cout, __LINE__, __FILE__);
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window.Init();
	window.InitContext();

	preload(*this);

	while (true)
	{
		HandleSceneLoading();

		priv::UpdateLimiter::Begin();

		if (Input::HasQuit()) break;

		// render step delta between frames
		priv::TimeUpd::UpdateRDelta();

		accumulator += priv::TimeUpd::RDeltaTime();

		// fuzzy timing
		while (accumulator > 1.0f/(targetUpdateRate + 1.0f))
		{
			priv::InputUpd::InputPoll();

			// update entities

			for (std::unique_ptr<Entity>& entity : entities)
			{
				EntityUpdate(*entity);
			}

			// update time
			priv::TimeUpd::IncUpdFrames();
			priv::TimeUpd::UpdateDelta(); // delta between logic steps

			priv::UpdateLimiter::CalcUpdatesPerSecond();

			accumulator -= 1.0f / (targetUpdateRate - 1.0f);
			if (accumulator < 0) accumulator = 0;
		}
		renderer.Render(entities, *this);

		window.SwapBuffer();

		priv::TimeUpd::IncRdrFrames();
		priv::UpdateLimiter::CalcRendersPerSecond();

		std::cout << "Renders/s: " << priv::UpdateLimiter::GetRendersPerSecond() << " Updates/s: " << priv::UpdateLimiter::GetUpdatesPerSecond() << '\n';

		priv::UpdateLimiter::End(targetFramerate);
	}
}

void won::Game::SetActiveCamera(Entity* camera)
{
	cmp::Camera* cameraCmp = camera->GetComponent<cmp::Camera>();

	if (cameraCmp == nullptr)
		Error::ThrowError("Entity does not contain a Camera component.", std::cout, __LINE__, __FILE__);

	renderer.SetActiveCamera(cameraCmp);
}

void won::Game::LoadScene(int index)
{
	nextSceneToLoad = index;
}

int won::Game::GetWidth() const
{
	return window.GetWidth();
}

int won::Game::GetHeight() const
{
	return window.GetHeight();
}

void won::Game::EntityInit(Entity& entity)
{
	for (Component* cmp : entity.GetComponents())
	{
		cmp->Init();
	}
}

void won::Game::EntityUpdate(Entity& entity)
{
	for (Component* cmp : entity.GetComponents())
	{
		cmp->Update();
	}
}

void won::Game::Render()
{
	

	while (true)
	{
		if (Input::HasQuit()) break;

		
	}
}

void won::Game::HandleSceneLoading()
{
	if (nextSceneToLoad == -1) return;

	Scene* scene = scenes[nextSceneToLoad];

	entities.clear();

	scene->Init(*this);

	nextSceneToLoad = -1;
}
