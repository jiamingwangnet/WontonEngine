#pragma once

#include <WontonEngine/Game.h>
#include <WontonEngine/Defaults.h>
#include <WontonEngine/Rendering/Texture.h>
#include <WontonEngine/Rendering/Material.h>
#include "Spin.h"
#include "CameraController.h"

void preload(won::Game& game)
{
	game.RegisterComponent<Spin>();
	game.RegisterComponent<CameraController>();

	won::Defaults::Load(won::Defaults::AssetType::All);

	won::TextureManager::CreateTexture("km", "./Assets/km.jpg");

	won::UniformDataList datalist;
	datalist.push_back(won::UniformData<won::Color>::GenData("bodyColor", won::UniformType::Color, { 255, 237, 186, 255 }));
	datalist.push_back(won::UniformData<won::Texture>::GenData("bgTexture", won::UniformType::Texture, won::TextureManager::GetTexture("km")));

	won::MaterialManager::CreateMaterial("km", won::ShaderManager::GetShader(won::Defaults::DEFAULT_SHADER_NAME), std::move(datalist));

	won::UniformDataList datalist2;
	datalist2.push_back(won::UniformData<won::Color>::GenData("bodyColor", won::UniformType::Color, { 10, 198, 50 }));
	datalist2.push_back(won::UniformData<won::Texture>::GenData("bgTexture", won::UniformType::Texture, won::TextureManager::GetTexture(won::Defaults::UNDEFINED_TEXTURE_NAME)));

	won::MaterialManager::CreateMaterial("Green", won::ShaderManager::GetShader(won::Defaults::DEFAULT_SHADER_NAME), std::move(datalist2));
}