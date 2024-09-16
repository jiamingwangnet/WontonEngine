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
	datalist.push_back(won::UniformData<won::Color>::GenData("diffuse", won::UniformType::Color, { 255, 237, 186, 255 }));
	datalist.push_back(won::UniformData<won::Color>::GenData("specular", won::UniformType::Color, { 0, 0, 0, 255 }));
	datalist.push_back(won::UniformData<won::Color>::GenData("ambient", won::UniformType::Color, { 20, 20, 20, 255 }));
	datalist.push_back(won::UniformData<won::Texture>::GenData("diffuseTexture", won::UniformType::Texture, won::TextureManager::GetTexture("km")));
	datalist.push_back(won::UniformData<float>::GenData("smoothness", won::UniformType::Float, 0.0f));

	won::MaterialManager::CreateMaterial("km", won::ShaderManager::GetShader(won::Defaults::DEFAULT_SHADER_NAME), std::move(datalist));

	won::UniformDataList datalist2;
	datalist2.push_back(won::UniformData<won::Color>::GenData("diffuse", won::UniformType::Color, { 10, 198, 50, 255 }));
	datalist2.push_back(won::UniformData<won::Color>::GenData("specular", won::UniformType::Color, { 20, 40, 20, 255 }));
	datalist2.push_back(won::UniformData<won::Color>::GenData("ambient", won::UniformType::Color, { 5, 80, 34, 255 }));
	datalist2.push_back(won::UniformData<won::Texture>::GenData("diffuseTexture", won::UniformType::Texture, won::TextureManager::GetTexture(won::Defaults::UNDEFINED_TEXTURE_NAME)));
	datalist2.push_back(won::UniformData<float>::GenData("smoothness", won::UniformType::Float, 1.0f / 64.0f));

	won::MaterialManager::CreateMaterial("Green", won::ShaderManager::GetShader(won::Defaults::DEFAULT_SHADER_NAME), std::move(datalist2));
}