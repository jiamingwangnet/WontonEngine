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

	won::Game game{ 800, 600, "Engine Test", (won::WinFlags)0, won::Color{30, 30, 30, 255}, preload, scenes, false, 0.0f, 65.0f };
	
	game.Start();

	return 0;
}