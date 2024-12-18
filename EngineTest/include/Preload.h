#pragma once

#include <WontonEngine/Game.h>
#include <WontonEngine/Defaults.h>
#include <WontonEngine/Rendering/Texture.h>
#include <WontonEngine/Rendering/Material.h>
#include "Spin.h"
#include "CameraController.h"
#include "DeleteComponent.h"

void preload(won::Game& game)
{
	game.RegisterComponent<Spin>();
	game.RegisterComponent<CameraController>();
	game.RegisterComponent<DeleteComponent>();

	won::Defaults::Load(won::Defaults::AssetType::All);
	won::ShaderManager::CreateShaderVF("jiggly", "shaders/jiggly.vert", won::Defaults::WON_DEFAULT_FRAGMENT_SHADER);

	won::TextureManager::CreateTexture("km", "./Assets/km.jpg");

	won::UniformDataList datalist;
	datalist.push_back(won::UniformData<won::Color>::GenData("diffuse", won::UniformType::Color, { 255, 237, 186, 255 }));
	datalist.push_back(won::UniformData<won::Color>::GenData("specular", won::UniformType::Color, { 255, 237, 186, 255 }));
	datalist.push_back(won::UniformData<won::Color>::GenData("ambient", won::UniformType::Color, { 255, 237, 186, 255 }));
	datalist.push_back(won::UniformData<won::Texture>::GenData("diffuseTexture", won::UniformType::Texture, won::TextureManager::GetTexture("km")));
	datalist.push_back(won::UniformData<float>::GenData("smoothness", won::UniformType::Float, 0.6f));

	won::MaterialManager::CreateMaterial("km", won::ShaderManager::GetShader("jiggly"), std::move(datalist));

	won::UniformDataList datalist2;
	datalist2.push_back(won::UniformData<won::Color>::GenData("diffuse", won::UniformType::Color, { 10, 198, 50, 255 }));
	datalist2.push_back(won::UniformData<won::Color>::GenData("specular", won::UniformType::Color, { 10, 198, 50, 255 }));
	datalist2.push_back(won::UniformData<won::Color>::GenData("ambient", won::UniformType::Color, { 10, 198, 50, 255 }));
	datalist2.push_back(won::UniformData<won::Texture>::GenData("diffuseTexture", won::UniformType::Texture, won::TextureManager::GetTexture(won::Defaults::UNDEFINED_TEXTURE_NAME)));
	datalist2.push_back(won::UniformData<float>::GenData("smoothness", won::UniformType::Float, 0.4f));

	won::MaterialManager::CreateMaterial("Green", won::ShaderManager::GetShader(won::Defaults::DEFAULT_SHADER_NAME), std::move(datalist2));

	won::UniformDataList datalist3;
	won::MaterialManager::CreateMaterial("PostProcess", won::ShaderManager::CreateShaderFF("PostShader", won::Defaults::WON_POST_PROCESSING_VERTEX_SHADER, "shaders/postproc.frag"), std::move(datalist3));

	won::UniformDataList datalist4;
	won::MaterialManager::CreateMaterial("PostProcess1", won::ShaderManager::CreateShaderFF("PostShader1", won::Defaults::WON_POST_PROCESSING_VERTEX_SHADER, "shaders/bwpost.frag"), std::move(datalist4));
	
	won::UniformDataList datalist5;
	won::MaterialManager::CreateMaterial("PostProcess2", won::ShaderManager::CreateShaderFF("PostShader2", won::Defaults::WON_POST_PROCESSING_VERTEX_SHADER, "shaders/postproc2.frag"), std::move(datalist5));
}