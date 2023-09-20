#pragma once

#include "Window.h"
#include <functional>
#include "Scene.h"
#include "Rendering/ScreenRenderer.h"
#include "Entity.h"
#include <thread>

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
		void LoadScene(int index);

	private:
		void EntityInit(Entity& entity);
		void EntityUpdate(Entity& entity);
		void EntityRender(Entity& entity);

		void Render(); // for the render thread

	private:
		priv::Window window;
		priv::ScreenRenderer renderer;

		preload_func preload;
		std::vector<Scene*> scenes;

		std::thread renderThread;
	};
}