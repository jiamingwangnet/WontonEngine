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
	datalist.push_back(won::UniformData<won::Vector3>::GenData("bodyColor", won::UniformType::Vec3, { 1.0f, 237.0f/255.0f, 186.0f/255.0f }));
	datalist.push_back(won::UniformData<won::Texture>::GenData("bgTexture", won::UniformType::Texture, won::TextureManager::GetTexture("km")));

	won::MaterialManager::CreateMaterial("km", won::ShaderManager::GetShader(won::Defaults::DEFAULT_SHADER_NAME), std::move(datalist));
}