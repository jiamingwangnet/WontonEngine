#pragma once

#include "Window.h"
#include <functional>
#include "Scene.h"
#include "Rendering/ScreenRenderer.h"
#include "Entity.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "ECManager.h"

namespace won
{
	class Game
	{
	public:
		using preload_func = std::function<void(Game&)>;
	public:
		Game(int width, int height, const std::string& name, WinFlags flags, Color clear, preload_func preload, const std::vector<Scene*> scenes, bool vsync = true, float targetFramerate = 60.0f, float targetUpdateRate = 60.0f);
		Game() = delete;
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		void Start();
		void SetActiveCamera(Entity camera);

		template<class Creator>
		Entity CreateEntity();
		void LoadScene(int index);  // sets the next scene to load

		int GetWidth() const;
		int GetHeight() const;

		template<class T>
		void RegisterComponent();
		
		void DestroyEntity(Entity entity);

		priv::ScreenRenderer& GetRenderer();
	private:
		void HandleSceneLoading(); // gets the next scene to load and loads it

	private:
		priv::Window window;
		priv::ScreenRenderer renderer;

		preload_func preload;
		std::vector<Scene*> scenes;

		int nextSceneToLoad = 0; // default to -1 if there is no scene
		float targetFramerate;
		float targetUpdateRate;

		float accumulator = 0.0;

		static priv::ComponentManager compManager;
		static priv::EntityManager entityManager;

		friend class priv::ECManager;
	};

	template<class Creator>
	inline Entity Game::CreateEntity()
	{
		Creator cr{};
		Entity entity = entityManager.CreateEntity();
		cr.Create(entity);
		return entity;
	}
	template<class T>
	inline void Game::RegisterComponent()
	{
		compManager.RegisterComponent<T>();
	}
}