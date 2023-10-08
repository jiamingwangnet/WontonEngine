#pragma once

#include <WontonEngine/Game.h>
#include <WontonEngine/Defaults.h>
#include <WontonEngine/Rendering/Texture.h>
#include <WontonEngine/Rendering/Material.h>

void preload(won::Game& game)
{
	won::Defaults::Load(won::Defaults::AssetType::All);

	won::TextureManager::CreateTexture("km", "./Assets/km.jpg");

	won::UniformDataList datalist;
	datalist.push_back(won::UniformData<won::Color>::GenData("bodyColor", won::UniformType::Color, { 255, 237, 186, 255 }));
	datalist.push_back(won::UniformData<won::Texture>::GenData("bgTexture", won::UniformType::Texture, won::TextureManager::GetTexture("km")));

	won::MaterialManager::CreateMaterial("km", won::ShaderManager::GetShader(won::Defaults::DEFAULT_SHADER_NAME), std::move(datalist));
}