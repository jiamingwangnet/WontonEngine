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

	won::Game game{ 800, 600, "Engine Test", (won::WinFlags)won::WinFlags::Resizable, won::Color{30, 30, 30, 255}, preload, scenes, false, 0.0f, 60.0f, 256, 224 };
	
	game.Start();

	return 0;
}