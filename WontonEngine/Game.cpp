#include "include/WontonEngine/Game.h"
#include "include/WontonEngine/Components/Camera.h"
#include "include/WontonEngine/Input.h"
#include "include/WontonEngine/Time.h"
#include "include/WontonEngine/Entity.h"
#include <iostream>

std::thread::id won::Game::mainThreadId = std::this_thread::get_id();

won::Game::Game(int width, int height, const std::string& name, WinFlags flags, Color clear, preload_func preload, const std::vector<Scene*> scenes, bool vsync)
	: window{width, height, name, flags, clear, vsync}, preload{preload}, scenes{scenes}
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
	renderThread = std::thread{ &Game::Render, this };

	// wait until preloading is done
	std::unique_lock lock{ preloadLock };
	condv.wait(lock);

	while (true)
	{
		HandleSceneLoading();

		priv::InputUpd::InputPoll();

		if (Input::HasQuit()) break;

		// update entities
		entityMutex.lock();

		for (std::unique_ptr<Entity>& entity : entities)
		{
			EntityUpdate(*entity);
		}

		entityMutex.unlock();

		// update time

		priv::TimeUpd::IncUpdFrames();
	}

	renderThread.join();
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

std::thread::id won::Game::GetMainThreadId()
{
	return Game::mainThreadId;
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

void won::Game::EntityRender(Entity& entity)
{
	for (Component* cmp : entity.GetComponents())
	{
		cmp->Render();
	}
}

void won::Game::Render()
{
	preloadLock.lock();

	window.InitContext();
	preload(*this);

	preloadLock.unlock();

	condv.notify_one();

	while (true)
	{
		if (Input::HasQuit()) break;

		entityMutex.lock();

		for (std::unique_ptr<Entity>& entity : entities)
		{
			EntityRender(*entity);
		}

		renderer.Render(entities, *this);

		entityMutex.unlock();

		window.SwapBuffer();

		priv::TimeUpd::IncRdrFrames();
	}
}

void won::Game::HandleSceneLoading()
{
	if (nextSceneToLoad == -1) return;

	Scene* scene = scenes[nextSceneToLoad];

	entityMutex.lock();
	entities.clear();
	entityMutex.unlock();

	scene->Init(*this);

	nextSceneToLoad = -1;
}
