#include "include/WontonEngine/Defaults.h"
#include "include/WontonEngine/Rendering/Shader.h"
#include "include/WontonEngine/Rendering/Material.h"
#include "include/WontonEngine/Rendering/Mesh.h"
#include "include/WontonEngine/Rendering/Texture.h"
#include "include/WontonEngine/Components/Transform.h"
#include "include/WontonEngine/Components/Renderer.h"
#include "include/WontonEngine/Components/Light.h"
#include "include/WontonEngine/Constants.h"

const std::vector<won::Vertex> won::Defaults::box_vertices
{
	//            positions               UV                Colors

	// +/- z
	won::Vertex{{ 0.5f,  0.5f,  0.5f},	 {1.0f, 1.0f},      {0,0,0,0},     { 0.0f,  0.0f,  1.0f}}, // top right
	won::Vertex{{ 0.5f, -0.5f,  0.5f},   {1.0f, 0.0f},      {0,0,0,0},     { 0.0f,  0.0f,  1.0f}}, // bottom right
	won::Vertex{{-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0},     { 0.0f,  0.0f,  1.0f}}, // bottom left
	won::Vertex{{-0.5f,  0.5f,  0.5f},	 {0.0f, 1.0f},      {0,0,0,0},     { 0.0f,  0.0f,  1.0f}}, // top left 

	won::Vertex{{ 0.5f,  0.5f, -0.5f},   {1.0f, 1.0f},      {0,0,0,0},     { 0.0f,  0.0f, -1.0f}}, // top right
	won::Vertex{{ 0.5f, -0.5f, -0.5f},   {1.0f, 0.0f},      {0,0,0,0},     { 0.0f,  0.0f, -1.0f}}, // bottom right
	won::Vertex{{-0.5f, -0.5f, -0.5f},   {0.0f, 0.0f},      {0,0,0,0},     { 0.0f,  0.0f, -1.0f}}, // bottom left
	won::Vertex{{-0.5f,  0.5f, -0.5f},   {0.0f, 1.0f},      {0,0,0,0},     { 0.0f,  0.0f, -1.0f}}, // top left 

	// +/- y FIXME
	won::Vertex{{ 0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},      {0,0,0,0},     { 0.0f,  1.0f,  0.0f}}, // top right
	won::Vertex{{ 0.5f,  0.5f,  0.5f},   {1.0f, 0.0f},      {0,0,0,0},     { 0.0f,  1.0f,  0.0f}}, // bottom right
	won::Vertex{{-0.5f,  0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0},     { 0.0f,  1.0f,  0.0f}}, // bottom left
	won::Vertex{{-0.5f,  0.5f, -0.5f},	 {0.0f, 1.0f},      {0,0,0,0},     { 0.0f,  1.0f,  0.0f}}, // top left 

	won::Vertex{{ 0.5f, -0.5f, -0.5f},	 {1.0f, 1.0f},      {0,0,0,0},     { 0.0f, -1.0f,  0.0f}}, // top right
	won::Vertex{{ 0.5f, -0.5f,  0.5f},   {1.0f, 0.0f},      {0,0,0,0},     { 0.0f, -1.0f,  0.0f}}, // bottom right
	won::Vertex{{-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0},     { 0.0f, -1.0f,  0.0f}}, // bottom left
	won::Vertex{{-0.5f, -0.5f, -0.5f},	 {0.0f, 1.0f},      {0,0,0,0},     { 0.0f, -1.0f,  0.0f}}, // top left 

	// +/- x FIXME
	won::Vertex{{ 0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},      {0,0,0,0},     { 1.0f,  0.0f,  0.0f}}, // top right
	won::Vertex{{ 0.5f, -0.5f, -0.5f},   {1.0f, 0.0f},      {0,0,0,0},     { 1.0f,  0.0f,  0.0f}}, // bottom right
	won::Vertex{{ 0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0},     { 1.0f,  0.0f,  0.0f}}, // bottom left
	won::Vertex{{ 0.5f,  0.5f,  0.5f},	 {0.0f, 1.0f},      {0,0,0,0},     { 1.0f,  0.0f,  0.0f}}, // top left 

	won::Vertex{{-0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},      {0,0,0,0},     {-1.0f,  0.0f,  0.0f}}, // top right    0
	won::Vertex{{-0.5f, -0.5f, -0.5f},   {1.0f, 0.0f},      {0,0,0,0},     {-1.0f,  0.0f,  0.0f}}, // bottom right 1
	won::Vertex{{-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0},     {-1.0f,  0.0f,  0.0f}}, // bottom left  2
	won::Vertex{{-0.5f,  0.5f,  0.5f},	 {0.0f, 1.0f},      {0,0,0,0},     {-1.0f,  0.0f,  0.0f}}  // top left     3
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

const std::vector<won::Vertex> won::Defaults::plane_vertices
{
	won::Vertex{{ 0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},      {0,0,0,0},     { 0.0f,  1.0f,  0.0f}}, // top right
	won::Vertex{{ 0.5f,  0.5f,  0.5f},   {1.0f, 0.0f},      {0,0,0,0},     { 0.0f,  1.0f,  0.0f}}, // bottom right
	won::Vertex{{-0.5f,  0.5f,  0.5f},   {0.0f, 0.0f},      {0,0,0,0},     { 0.0f,  1.0f,  0.0f}}, // bottom left
	won::Vertex{{-0.5f,  0.5f, -0.5f},	 {0.0f, 1.0f},      {0,0,0,0},     { 0.0f,  1.0f,  0.0f}}, // top left 
};

const std::vector<unsigned int> won::Defaults::plane_indices
{
	2, 0, 1,
	0, 2, 3
};

const std::string won::Defaults::vertexShader = R"SHADER(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;
layout (location = 3) in vec3 normal;

out vec2 texCoord;
out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 won_ModelViewProjMatrix;
uniform mat4 won_ModelMatrix;
uniform mat3 won_NormalMatrix;

void main()
{
	gl_Position = won_ModelViewProjMatrix * vec4(position.xyz, 1.0);
	texCoord = uv;
	fragNormal = won_NormalMatrix * normal;
	fragPos = vec3(won_ModelMatrix * vec4(position, 1.0));
}
)SHADER";

const std::string won::Defaults::fragmentShader = R"SHADER(
#version 330 core

out vec4 FragColor;

in vec2 texCoord;
in vec3 fragNormal;
in vec3 fragPos;

uniform vec4 diffuse;
uniform sampler2D diffuseTexture;
uniform vec4 specular;
uniform vec4 ambient;
uniform float smoothness;

uniform vec3 won_ViewPosition;

// TODO: extract into file later
struct won_Light
{
	int type;

	vec3 position;
	vec3 direction;

	vec4 color;
	float ambientStrength;

	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;
};
#define WON_MAX_LIGHTS )SHADER" S_WON_MAX_LIGHTS
R"SHADER(
uniform won_Light won_Lights[WON_MAX_LIGHTS];
uniform int won_NumLights;

vec4 won_CalcPointLight(won_Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 tdiffuse, vec3 tambient)
{
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));

	float smoothm = smoothness * 128.0;

	vec3 lightDir = normalize(light.position - fragPos);
	vec3 reflectLight = reflect(-lightDir, normal);

	float diff = max(dot(normal,lightDir), 0.0);
	float spec = pow(max(dot(viewDir, reflectLight), 0.0), smoothm);

	vec3 ldiffuse = light.color.a * light.color.rgb * diff * tdiffuse.rgb;
	vec3 lspecular = light.color.a * light.color.rgb * spec * specular.rgb;
	vec3 lambient = light.ambientStrength * light.color.rgb * tambient.rgb;

	ldiffuse *= attenuation;
	lspecular *= attenuation;
	lambient *= attenuation;

	return vec4(ldiffuse + lambient + lspecular, 0.0);
}

vec4 won_CalcDirectionalLight(won_Light light, vec3 normal, vec3 viewDir, vec3 tdiffuse, vec3 tambient)
{
	float smoothm = smoothness * 128.0;

	vec3 lightDir = normalize(-light.direction);
	vec3 reflectLight = reflect(-lightDir, normal);

	float diff = max(dot(normal,lightDir), 0.0);
	float spec = pow(max(dot(viewDir, reflectLight), 0.0), smoothm);

	vec3 ldiffuse = light.color.a * light.color.rgb * diff * tdiffuse.rgb;
	vec3 lspecular = light.color.a * light.color.rgb * spec * specular.rgb;
	vec3 lambient = light.ambientStrength * light.color.rgb * tambient.rgb;

	return vec4(ldiffuse + lambient + lspecular, 0.0);
}

vec4 won_CalcSpotLight(won_Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 tdiffuse, vec3 tambient)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction));

	if(theta > light.outerCutOff)
	{
		float epsilon = light.cutOff - light.outerCutOff;
		float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
		float smoothm = smoothness * 128.0;

		float distance = length(light.position - fragPos);
		float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));

		vec3 reflectLight = reflect(-lightDir, normal);

		float diff = max(dot(normal,lightDir), 0.0);
		float spec = pow(max(dot(viewDir, reflectLight), 0.0), smoothm);

		vec3 ldiffuse = light.color.a * light.color.rgb * diff * tdiffuse.rgb;
		vec3 lspecular = light.color.a * light.color.rgb * spec * specular.rgb;
		vec3 lambient = light.ambientStrength * light.color.rgb * tambient.rgb;

		ldiffuse  *= intensity;
		lspecular *= intensity;

		ldiffuse *= attenuation;
		lspecular *= attenuation;
		lambient *= attenuation;

		return vec4(ldiffuse + lambient + lspecular, 0.0);
	}
	return vec4(light.ambientStrength * light.color.rgb * tambient.rgb, 0.0);
}

void main()
{
	vec3 norm = normalize(fragNormal);
	vec4 lighting = vec4(0.0);
	vec4 tex = texture(diffuseTexture, texCoord);
	vec3 tdiff = (tex * diffuse).rgb;
	vec3 tambi = (tex * ambient).rgb;
	vec3 viewDir = normalize(won_ViewPosition - fragPos);

	for(int i = 0; i < won_NumLights; i++)
	{
		switch(won_Lights[i].type)
		{
		case 0:
			lighting += won_CalcDirectionalLight(won_Lights[i], norm, viewDir, tdiff, tambi);
			break;
		case 1:
			lighting += won_CalcPointLight(won_Lights[i], norm, fragPos, viewDir, tdiff, tambi);
			break;
		case 2:
			lighting += won_CalcSpotLight(won_Lights[i], norm, fragPos, viewDir, tdiff, tambi);
		}
	}

	FragColor = vec4(lighting.rgb, diffuse.a);
}
)SHADER";

void won::Defaults::Load(AssetType type)
{
	switch (type)
	{
	case AssetType::All:
		LoadShader();
		LoadBoxMesh();
		LoadPlaneMesh();
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
	case AssetType::PlaneMesh:
		LoadPlaneMesh();
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

	datalist.push_back(UniformData<Color>::GenData("diffuse", UniformType::Color, { 140, 140, 140, 255 }));
	datalist.push_back(UniformData<Texture>::GenData("diffuseTexture", UniformType::Texture, TextureManager::GetTexture(UNDEFINED_TEXTURE_NAME)));
	datalist.push_back(UniformData<Color>::GenData("specular", UniformType::Color, { 20, 20, 20, 255 }));
	datalist.push_back(UniformData<Color>::GenData("ambient", UniformType::Color, { 0, 0, 0, 255 }));
	datalist.push_back(UniformData<float>::GenData("smoothness", UniformType::Float, 1.0f / 128.0f));

	MaterialManager::CreateMaterial(DEFAULT_MATERIAL_NAME, ShaderManager::GetShader(DEFAULT_SHADER_NAME), std::move(datalist));
}

void won::Defaults::LoadBoxMesh()
{
	MeshManager::CreateMesh(BOX_MESH_NAME, box_vertices, box_indices);
}

void won::Defaults::LoadPlaneMesh()
{
	MeshManager::CreateMesh(PLANE_MESH_NAME, plane_vertices, plane_indices);
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

void won::Defaults::Plane::Create(Entity& entity) const
{
	entity.AddComponent<cmp::Transform>(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 1.0f, 1.0f, 1.0f }, Vector3{ 0.0f, 0.0f, 0.0f });
	entity.AddComponent<cmp::Renderer>(MaterialManager::GetMaterial(DEFAULT_MATERIAL_NAME), MeshManager::GetMesh(PLANE_MESH_NAME));
}

void won::Defaults::PointLight::Create(Entity& entity) const
{
	entity.AddComponent<cmp::Transform>(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });
	cmp::Light* light = entity.AddComponent<cmp::Light>(LightType::Point, Color{ 100, 100, 100, 0xff }, 0.1f, 1.0f);
	light->SetPointLinear(0.045f);
	light->SetPointQuadratic(0.0075f);
}

void won::Defaults::DirectionalLight::Create(Entity& entity) const
{
	entity.AddComponent<cmp::Transform>(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });
	entity.AddComponent<cmp::Light>(LightType::Directional, Color{ 200, 200, 200, 0xff }, 0.3f, 1.0f);
}

void won::Defaults::SpotLight::Create(Entity& entity) const
{
	entity.AddComponent<cmp::Transform>(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });
	cmp::Light* light = entity.AddComponent<cmp::Light>(LightType::Spot, Color{ 150, 150, 150, 0xff }, 0.0f, 1.0f);
	light->SetCutOff(10.0f);
	light->SetOuterCutOff(15.0f);
	light->SetPointLinear(0.007f);
	light->SetPointQuadratic(0.0002f);
}
