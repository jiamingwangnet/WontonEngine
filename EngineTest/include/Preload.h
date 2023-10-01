#pragma once

#include <WontonEngine/Game.h>
#include <WontonEngine/Defaults.h>

void preload(won::Game& game)
{
	won::Defaults::Load(won::Defaults::AssetType::All);
}