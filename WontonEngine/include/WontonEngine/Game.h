#pragma once

#include "Window.h"
#include <functional>
#include "Scene.h"
#include "Rendering/ScreenRenderer.h"
#include "Entity.h"
#include <thread>
#include <mutex>
#include <condition_variable>

namespace won
{
	class Game
	{
	public:
		using preload_func = std::function<void(Game&)>;
	public:
		Game(int width, int height, const std::string& name, WinFlags flags, Color clear, preload_func preload, const std::vector<Scene*> scenes, bool vsync = true);

		void Start();
		void SetActiveCamera(Entity* camera);

		template<class Creator>
		Entity* CreateEntity();
		void LoadScene(int index);  // sets the next scene to load

		int GetWidth() const;
		int GetHeight() const;

		static std::thread::id GetMainThreadId();

	private:
		void EntityInit(Entity& entity);
		void EntityUpdate(Entity& entity);

		void Render(); // for the render thread

		void HandleSceneLoading(); // gets the next scene to load and loads it
	private:
		priv::Window window;
		priv::ScreenRenderer renderer;

		preload_func preload;
		std::vector<Scene*> scenes;

		std::mutex entityMutex;
		std::vector<std::unique_ptr<Entity>> entities;

		std::mutex preloadLock; // make sure the game doesn't start updating till preloading is done
		std::condition_variable condv;

		std::thread renderThread;

		int nextSceneToLoad = 0; // default to -1 if there is no scene

		static std::thread::id mainThreadId;
	};
	template<class Creator>
	inline Entity* Game::CreateEntity()
	{
		entities.push_back(std::make_unique<Entity>(*this));
		Creator cr;
		cr.Create(*entities.back());

		return entities.back().get();
	}
}