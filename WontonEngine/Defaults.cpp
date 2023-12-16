#include "include/WontonEngine/Defaults.h"
#include "include/WontonEngine/Rendering/Shader.h"
#include "include/WontonEngine/Rendering/Material.h"
#include "include/WontonEngine/Rendering/Mesh.h"
#include "include/WontonEngine/Rendering/Texture.h"
#include "include/WontonEngine/Components/Transform.h"
#include "include/WontonEngine/Components/Renderer.h"

const std::vector<won::Vertex> won::Defaults::box_vertices
{
	//            positions               UV                Colors

	// +/- z
	won::Vertex{{ 0.5f,  0.5f,  0.5f},	 {1.0f, 1.0f},      {0,0,0,0}}, // top right
	won::Vertex{{ 0.5f, -0.5f,  0.5f},   {1.0f, 0.0f},      {0,0,0,0}}, // bottom right
	won::Vertex{{-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0}}, // bottom left
	won::Vertex{{-0.5f,  0.5f,  0.5f},	 {0.0f, 1.0f},      {0,0,0,0}}, // top left 

	won::Vertex{{ 0.5f,  0.5f, -0.5f},   {1.0f, 1.0f},      {0,0,0,0}}, // top right
	won::Vertex{{ 0.5f, -0.5f, -0.5f},   {1.0f, 0.0f},      {0,0,0,0}}, // bottom right
	won::Vertex{{-0.5f, -0.5f, -0.5f},   {0.0f, 0.0f},      {0,0,0,0}}, // bottom left
	won::Vertex{{-0.5f,  0.5f, -0.5f},   {0.0f, 1.0f},      {0,0,0,0}}, // top left 

	// +/- y FIXME
	won::Vertex{{ 0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},      {0,0,0,0}}, // top right
	won::Vertex{{ 0.5f,  0.5f,  0.5f},   {1.0f, 0.0f},      {0,0,0,0}}, // bottom right
	won::Vertex{{-0.5f,  0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0}}, // bottom left
	won::Vertex{{-0.5f,  0.5f, -0.5f},	 {0.0f, 1.0f},      {0,0,0,0}}, // top left 

	won::Vertex{{ 0.5f, -0.5f, -0.5f},	 {1.0f, 1.0f},      {0,0,0,0}}, // top right
	won::Vertex{{ 0.5f, -0.5f,  0.5f},   {1.0f, 0.0f},      {0,0,0,0}}, // bottom right
	won::Vertex{{-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0}}, // bottom left
	won::Vertex{{-0.5f, -0.5f, -0.5f},	 {0.0f, 1.0f},      {0,0,0,0}}, // top left 

	// +/- x FIXME
	won::Vertex{{ 0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},      {0,0,0,0}}, // top right
	won::Vertex{{ 0.5f, -0.5f, -0.5f},   {1.0f, 0.0f},      {0,0,0,0}}, // bottom right
	won::Vertex{{ 0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0}}, // bottom left
	won::Vertex{{ 0.5f,  0.5f,  0.5f},	 {0.0f, 1.0f},      {0,0,0,0}}, // top left 

    won::Vertex{{-0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},      {0,0,0,0}}, // top right    0
	won::Vertex{{-0.5f, -0.5f, -0.5f},   {1.0f, 0.0f},      {0,0,0,0}}, // bottom right 1
	won::Vertex{{-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0}}, // bottom left  2
	won::Vertex{{-0.5f,  0.5f,  0.5f},	 {0.0f, 1.0f},      {0,0,0,0}}  // top left     3
};

const std::vector<unsigned int> won::Defaults::box_indices
{
	2, 0, 1, // front
	0, 2, 3,

	6, 5, 4, // back
	4, 7, 6,

	10, 8, 9, // top
	8, 10, 11, 

	14, 13, 12, // bottom
	12, 15, 14,

	18, 16, 17, // right
	16, 18, 19,

	22, 21, 20, // left
	20, 23, 22
};

const std::string won::Defaults::vertexShader = R"V0G0N(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;

out vec2 texCoord;
out vec4 vertBodyColor;

uniform mat4 won_ProjectionMatrix;
uniform mat4 won_ViewMatrix;
uniform mat4 won_ModelMatrix;

uniform vec4 bodyColor;

void main()
{
	gl_Position = won_ProjectionMatrix * won_ViewMatrix * won_ModelMatrix * vec4(position.xyz, 1.0);
	texCoord = uv;
	vertBodyColor = bodyColor;
}
)V0G0N";

const std::string won::Defaults::fragmentShader = R"V0G0N(
#version 330 core

out vec4 FragColor;

in vec2 texCoord;
in vec4 vertBodyColor;

uniform sampler2D bgTexture;

void main()
{
	FragColor = texture(bgTexture, texCoord) * vec4(vertBodyColor.rgb, 1.0);
}
)V0G0N";

void won::Defaults::Load(AssetType type)
{
	switch (type)
	{
	case AssetType::All:
		LoadShader();
		LoadBoxMesh();
		LoadUndefinedTexture();
		LoadMaterial();
		break;
	case AssetType::DefaultShader:
		LoadShader();
		break;
	case AssetType::DefaultMaterial:
		LoadMaterial();
		break;
	case AssetType::BoxMesh:
		LoadBoxMesh();
		break;
	case AssetType::UndefinedTexture:
		LoadUndefinedTexture();
		break;
	}
}

void won::Defaults::LoadShader()
{
	ShaderManager::CreateShader(DEFAULT_SHADER_NAME, vertexShader, fragmentShader);
}

void won::Defaults::LoadMaterial()
{
	UniformDataList datalist;

	datalist.push_back(UniformData<Color>::GenData("bodyColor", UniformType::Color, { 255, 255, 255, 255 }));
	datalist.push_back(UniformData<Texture>::GenData("bgTexture", UniformType::Texture, TextureManager::GetTexture(UNDEFINED_TEXTURE_NAME)));

	MaterialManager::CreateMaterial(DEFAULT_MATERIAL_NAME, ShaderManager::GetShader(DEFAULT_SHADER_NAME), std::move(datalist));
}

void won::Defaults::LoadBoxMesh()
{
	MeshManager::CreateMesh(BOX_MESH_NAME, box_vertices, box_indices);
}

void won::Defaults::LoadUndefinedTexture()
{
	unsigned char data[3] = { 255, 255, 255 };
	TextureManager::CreateTexture(UNDEFINED_TEXTURE_NAME, data, 1, 1, false, TextureWrap::Repeat, TextureFilter::Nearest, TextureFilter::Nearest);
}

void won::Defaults::Box::Create(Entity& entity) const
{
	entity.AddComponent<cmp::Transform>(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 1.0f, 1.0f, 1.0f }, Vector3{ 0.0f, 0.0f, 0.0f });
	entity.AddComponent<cmp::Renderer>(MaterialManager::GetMaterial(DEFAULT_MATERIAL_NAME), MeshManager::GetMesh(BOX_MESH_NAME));
}
