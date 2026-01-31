#include <WontonEngine/Game.h>
#include "include/Preload.h"
#include <WontonEngine/Rendering/Material.h>
#include <WontonEngine/Scene.h>
#include <vector>
#include "include/MainScene.h"
#include "include/KMScene.h"

int main()
{
	MainScene mainScene;
	KMScene kmScene;

	std::vector<won::Scene*> scenes{&mainScene, &kmScene};

	// creates a 800x600 window with an OpenGL context resolution of 256x224
	/*static constexpr int WINDOW_X = 800;
	static constexpr int WINDOW_Y = 600;
	static constexpr int CONTEXT_X = 256;
	static constexpr int CONTEXT_Y = 224;*/

	// creates a 1280x720 window with an OpenGL context resolution of 1280x720
	static constexpr int WINDOW_X = 1280;
	static constexpr int WINDOW_Y = 720;
	static constexpr int CONTEXT_X = 1280;
	static constexpr int CONTEXT_Y = 720;

	
	won::Game game{ WINDOW_X, WINDOW_Y, "Engine Test", (won::WinFlags)won::WinFlags::Resizable, won::Color{30, 30, 30, 255}, preload, scenes, false, 0.0f, 60.0f, CONTEXT_X, CONTEXT_Y };
	
	game.Start();

	return 0;
}