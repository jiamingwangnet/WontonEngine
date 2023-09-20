#include <WontonEngine/Game.h>
#include "include/Preload.h"
#include <WontonEngine/Scene.h>
#include <vector>

int main()
{
	std::vector<won::Scene*> scenes;

	won::Game game{ 800, 600, "Engine Test", (won::WinFlags)0, won::Color{10, 10, 10, 10}, preload, scenes };

	game.Start();

	return 0;
}