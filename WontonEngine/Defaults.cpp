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
	//            positions               UV                Normals

	// +/- z
	won::Vertex{{ 0.5f,  0.5f,  0.5f},	 {1.0f, 1.0f},     { 0.0f,  0.0f,  1.0f}}, // top right
	won::Vertex{{ 0.5f, -0.5f,  0.5f},   {1.0f, 0.0f},     { 0.0f,  0.0f,  1.0f}}, // bottom right
	won::Vertex{{-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},     { 0.0f,  0.0f,  1.0f}}, // bottom left
	won::Vertex{{-0.5f,  0.5f,  0.5f},	 {0.0f, 1.0f},     { 0.0f,  0.0f,  1.0f}}, // top left 

	won::Vertex{{ 0.5f,  0.5f, -0.5f},   {1.0f, 1.0f},     { 0.0f,  0.0f, -1.0f}}, // top right
	won::Vertex{{ 0.5f, -0.5f, -0.5f},   {1.0f, 0.0f},     { 0.0f,  0.0f, -1.0f}}, // bottom right
	won::Vertex{{-0.5f, -0.5f, -0.5f},   {0.0f, 0.0f},     { 0.0f,  0.0f, -1.0f}}, // bottom left
	won::Vertex{{-0.5f,  0.5f, -0.5f},   {0.0f, 1.0f},     { 0.0f,  0.0f, -1.0f}}, // top left 

	// +/- y FIXME
	won::Vertex{{ 0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},     { 0.0f,  1.0f,  0.0f}}, // top right
	won::Vertex{{ 0.5f,  0.5f,  0.5f},   {1.0f, 0.0f},     { 0.0f,  1.0f,  0.0f}}, // bottom right
	won::Vertex{{-0.5f,  0.5f,  0.5f},   {0.0f, 0.0f},     { 0.0f,  1.0f,  0.0f}}, // bottom left
	won::Vertex{{-0.5f,  0.5f, -0.5f},	 {0.0f, 1.0f},     { 0.0f,  1.0f,  0.0f}}, // top left 

	won::Vertex{{ 0.5f, -0.5f, -0.5f},	 {1.0f, 1.0f},     { 0.0f, -1.0f,  0.0f}}, // top right
	won::Vertex{{ 0.5f, -0.5f,  0.5f},   {1.0f, 0.0f},     { 0.0f, -1.0f,  0.0f}}, // bottom right
	won::Vertex{{-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},     { 0.0f, -1.0f,  0.0f}}, // bottom left
	won::Vertex{{-0.5f, -0.5f, -0.5f},	 {0.0f, 1.0f},     { 0.0f, -1.0f,  0.0f}}, // top left 

	// +/- x
	won::Vertex{{ 0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},     { 1.0f,  0.0f,  0.0f}}, // top right
	won::Vertex{{ 0.5f, -0.5f, -0.5f},   {1.0f, 0.0f},     { 1.0f,  0.0f,  0.0f}}, // bottom right
	won::Vertex{{ 0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},     { 1.0f,  0.0f,  0.0f}}, // bottom left
	won::Vertex{{ 0.5f,  0.5f,  0.5f},	 {0.0f, 1.0f},     { 1.0f,  0.0f,  0.0f}}, // top left 

	won::Vertex{{-0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},     {-1.0f,  0.0f,  0.0f}}, // top right    0
	won::Vertex{{-0.5f, -0.5f, -0.5f},   {1.0f, 0.0f},     {-1.0f,  0.0f,  0.0f}}, // bottom right 1
	won::Vertex{{-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f},     {-1.0f,  0.0f,  0.0f}}, // bottom left  2
	won::Vertex{{-0.5f,  0.5f,  0.5f},	 {0.0f, 1.0f},     {-1.0f,  0.0f,  0.0f}}  // top left     3
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
	won::Vertex{{ 0.5f,  0.5f, -0.5f},	 {1.0f, 1.0f},     { 0.0f,  1.0f,  0.0f}}, // top right
	won::Vertex{{ 0.5f,  0.5f,  0.5f},   {1.0f, 0.0f},     { 0.0f,  1.0f,  0.0f}}, // bottom right
	won::Vertex{{-0.5f,  0.5f,  0.5f},   {0.0f, 0.0f},     { 0.0f,  1.0f,  0.0f}}, // bottom left
	won::Vertex{{-0.5f,  0.5f, -0.5f},	 {0.0f, 1.0f},     { 0.0f,  1.0f,  0.0f}}, // top left 
};

const std::vector<unsigned int> won::Defaults::plane_indices
{
	2, 0, 1,
	0, 2, 3
};

const std::string won::Defaults::WON_DEFAULT_VERTEX_SHADER = R"SHADER(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec2 texCoord;
out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 won_ModelViewProjMatrix;
uniform mat4 won_ModelMatrix;
uniform mat3 won_NormalMatrix;

void main()
{
	//  lighting calculations should be done in world space
	gl_Position = won_ModelViewProjMatrix * vec4(position.xyz, 1.0);
	texCoord = uv;
	fragNormal = won_NormalMatrix * normal;
	fragPos = vec3(won_ModelMatrix * vec4(position, 1.0));
}
)SHADER";

const std::string won::Defaults::WON_DEFAULT_FRAGMENT_SHADER = R"SHADER(
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

#include <WON_LIGHTING_FUNCTIONS>

layout(std140) uniform Won_StaticUniforms
{                          
	mat4 won_ProjectionMatrix;					
	mat4 won_ViewMatrix;      
	vec4 won_ViewPosition;	
	int won_Frames;				
	int won_Time;                  
	int won_WindowWidth;           
	int won_WindowHeight;       
	float won_DownscaleFactor;   
};

#define WON_MAX_LIGHTS )SHADER" S_WON_MAX_LIGHTS
R"SHADER(

layout(std140) uniform Won_LightUniforms
{
	int won_NumLights;
	won_Light won_Lights[WON_MAX_LIGHTS];                                        
};

void main()
{
	vec3 norm = normalize(fragNormal);
	vec4 lighting = vec4(0.0);
	vec4 tex = texture(diffuseTexture, texCoord);
	vec3 tdiff = (tex * diffuse).rgb;
	vec3 tambi = (tex * ambient).rgb;
	vec3 viewDir = normalize(won_ViewPosition.xyz - fragPos);

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

const std::string won::Defaults::WON_LIGHTING_FUNC_SRC = R"SHADER(
struct won_Light
{
	vec4 position;    
	vec4 direction;   
	vec4 color;        
	int type;            
	float ambientStrength;
	float linear;        
	float quadratic;     
	float cutOff;        
	float outerCutOff;   
};

vec4 won_CalcPointLight(won_Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 tdiffuse, vec3 tambient)
{
	float distance = length(light.position.xyz - fragPos);
	float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));

	float smoothm = smoothness * 128.0;

	vec3 lightDir = normalize(light.position.xyz - fragPos);
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

	vec3 lightDir = normalize(-light.direction.xyz);
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
	vec3 lightDir = normalize(light.position.xyz - fragPos);
	float theta = dot(lightDir, normalize(-light.direction.xyz));

	if(theta > light.outerCutOff)
	{
		float epsilon = light.cutOff - light.outerCutOff;
		float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
		float smoothm = smoothness * 128.0;

		float distance = length(light.position.xyz - fragPos);
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
)SHADER";

const std::string won::Defaults::WON_POSTPROC_PIXELATE_FUNC_SRC = R"SHADER(
vec4 won_Pixelate(sampler2D pinput, vec2 texCoord, vec2 winSize, float pixelSize)
{
	vec2 pixelCoord = pixelSize * floor(winSize * texCoord / vec2(pixelSize, pixelSize)) / winSize;

	return texture(pinput, pixelCoord);
}

vec2 won_PixelateCoords(vec2 texCoord, vec2 winSize, float pixelSize)
{
	vec2 pixelCoord = pixelSize * floor(winSize * texCoord / vec2(pixelSize, pixelSize)) / winSize ;

	return pixelCoord;
}

vec2 won_PixelateFragCoords(vec2 fragCoord, float pixelSize)
{
	vec2 pixelCoord = pixelSize * floor(fragCoord / vec2(pixelSize, pixelSize));

	return pixelCoord;
}
)SHADER";

const std::string won::Defaults::WON_POSTPROC_COLORLIMIT_FUNC_SRC = R"SHADER(
vec4 won_ColorLimiterByFactor(vec4 cinput, float stepFactor)
{
	return vec4(stepFactor * floor(cinput.rgb / stepFactor), 1.0);
}

vec4 won_ColorLimiterByParts(vec4 cinput, float parts)
{
	return vec4(floor(cinput.rgb * parts)/(parts - 1.0), 1.0);
}
)SHADER";

const std::string won::Defaults::WON_POST_PROCESSING_VERTEX_SHADER = R"SHADER(
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

out vec2 won_TexCoords;

void main()
{
	won_TexCoords = uv;
	gl_Position = vec4(position, 0.0, 1.0);
}
)SHADER";

const std::string won::Defaults::WON_DEFAULT_PASSTHROUGH_FRAGMENT_SHADER = R"SHADER(
#version 330

out vec4 FragColor;
in vec2 won_TexCoords;

uniform sampler2D won_DownscaleBufferTexture;

layout(std140) uniform Won_StaticUniforms
{                          
	mat4 won_ProjectionMatrix;					
	mat4 won_ViewMatrix;      
	vec4 won_ViewPosition;	
	int won_Frames;				
	int won_Time;                  
	int won_WindowWidth;           
	int won_WindowHeight;
	float won_DownscaleFactor;
};

void main()
{
	FragColor = texture(won_DownscaleBufferTexture, won_TexCoords);
}
)SHADER";

const std::string won::Defaults::WON_UTIL_RANDOM_FUNC_SRC = R"SHADER(
/*
	Code by Spatial
	05 July 2013
*/

// A single iteration of Bob Jenkins' One-At-A-Time hashing algorithm.
uint hash(uint x)
{
	x += (x << 10u);
	x ^= (x >> 6u);
	x += (x << 3u);
	x ^= (x >> 11u);
	x += (x << 15u);
	return x;
}

// Compound versions of the hashing algorithm I whipped together.
uint hash(uvec2 v) { return hash(v.x ^ hash(v.y)); }
uint hash(uvec3 v) { return hash(v.x ^ hash(v.y) ^ hash(v.z)); }
uint hash(uvec4 v) { return hash(v.x ^ hash(v.y) ^ hash(v.z) ^ hash(v.w)); }

// Construct a float with half-open range [0:1] using low 23 bits.
// All zeroes yields 0.0, all ones yields the next smallest representable value below 1.0.
float floatConstruct(uint m)
{
	const uint ieeeMantissa = 0x007FFFFFu; // binary32 mantissa bitmask
	const uint ieeeOne = 0x3F800000u; // 1.0 in IEEE binary32

	m &= ieeeMantissa;                     // Keep only mantissa bits (fractional part)
	m |= ieeeOne;                          // Add fractional part to 1.0

	float  f = uintBitsToFloat(m);       // Range [1:2]
	return f - 1.0;                        // Range [0:1]
}



// Pseudo-random value in half-open range [0:1].
float won_Random(float x) { return floatConstruct(hash(floatBitsToUint(x))); }
float won_Random(vec2  v) { return floatConstruct(hash(floatBitsToUint(v))); }
float won_Random(vec3  v) { return floatConstruct(hash(floatBitsToUint(v))); }
float won_Random(vec4  v) { return floatConstruct(hash(floatBitsToUint(v))); }

float won_RandRange(float min, float max, vec2 seed)
{
	return clamp(floor(won_Random(seed) * (float(max) - float(min) + 1.0) + float(min)), min, max); // clamp incase random returns 1
}

float won_RandRange(float min, float max, vec3 seed)
{
	return clamp(floor(won_Random(seed) * (float(max) - float(min) + 1.0) + float(min)), min, max); // clamp incase random returns 1
}

float won_RandRange(float min, float max, vec4 seed)
{
	return clamp(floor(won_Random(seed) * (float(max) - float(min) + 1.0) + float(min)), min, max); // clamp incase random returns 1
}

float won_RandRange(float min, float max, float seed)
{
	return clamp(floor(won_Random(seed) * (float(max) - float(min) + 1.0) + float(min)), min, max); // clamp incase random returns 1
}


float won_RandRangeF(float min, float max, vec2 seed)
{
	return clamp(won_Random(seed) * (float(max) - float(min)) + float(min), min, max); // clamp incase random returns 1
}

float won_RandRangeF(float min, float max, vec3 seed)
{
	return clamp(won_Random(seed) * (float(max) - float(min)) + float(min), min, max); // clamp incase random returns 1
}

float won_RandRangeF(float min, float max, vec4 seed)
{
	return clamp(won_Random(seed) * (float(max) - float(min)) + float(min), min, max); // clamp incase random returns 1
}

float won_RandRangeF(float min, float max, float seed)
{
	return clamp(won_Random(seed) * (float(max) - float(min)) + float(min), min, max); // clamp incase random returns 1
}

)SHADER";

const std::string won::Defaults::WON_POSTPROC_NOISE_FUNC_SRC = R"SHADER(
#include <WON_UTILITY_RANDOM>

vec4 won_NoiseBW(vec2 seed, float min, float max)
{
	return vec4(won_RandRangeF(min, max, seed) * vec3(1.0), 1.0);
}

vec4 won_NoiseCL(vec2 seed, float min, float max)
{
	float s0 = won_Random(seed);
	float s1 = won_Random(seed * won_Random(seed));
	float s2 = won_Random(seed * won_Random(seed * won_Random(seed)));

	return vec4(won_RandRangeF(min, max, s0), won_RandRange(min, max, s1), won_RandRange(min, max, s2), 1.0);
}
)SHADER";

const std::string won::Defaults::WON_POSTPROC_DITHER_FUNC_SRC = R"SHADER(
vec4 won_BayerDither8x8(vec4 cinput, vec2 fragCoords, float strength)
{
	int x = clamp(int(mod(fragCoords.x, 8.0)), 0, 8);
	int y = clamp(int(mod(fragCoords.y, 8.0)), 0, 8);
	int idx = x + y * 8;
	
	int dither[8 * 8] = {
     0, 32, 8, 40, 2, 34, 10, 42, /* 8x8 Bayer ordered dithering */
    48, 16, 56, 24, 50, 18, 58, 26, /* pattern. Each input pixel */
    12, 44, 4, 36, 14, 46, 6, 38, /* is scaled to the 0..63 range */
    60, 28, 52, 20, 62, 30, 54, 22, /* before looking in this table */
     3, 35, 11, 43, 1, 33, 9, 41, /* to determine the action. */
    51, 19, 59, 27, 49, 17, 57, 25,
    15, 47, 7, 39, 13, 45, 5, 37,
    63, 31, 55, 23, 61, 29, 53, 21 }; 

	cinput *= 255.0;
	cinput += dither[idx] * strength;

	return vec4(cinput.rgb / 255.0, 1.0);
}

vec4 won_BayerDither4x4(vec4 cinput, vec2 fragCoords, float strength)
{
	int x = int(mod(fragCoords.x, 4.0));
	int y = int(mod(fragCoords.y, 4.0));
	int idx = x + y * 4;

	int dither[4 * 4] = {
		0, 8, 2, 10,
		12, 4, 14, 6,
		3, 11, 1, 9,
		15, 6, 13, 5
    }; 

	cinput *= 255.0;
	cinput += dither[idx] * strength;

	return vec4(cinput.rgb / 255.0, 1.0);
}
)SHADER";

const std::unordered_map<std::string, const std::string*> won::Defaults::nameToSource{
	{(std::string)WON_LIGHTING_FUNC_NAME, &WON_LIGHTING_FUNC_SRC},
	{(std::string)WON_POSTPROC_PIXELATE_FUNC_NAME, &WON_POSTPROC_PIXELATE_FUNC_SRC},
	{(std::string)WON_POSTPROC_COLORLIMIT_FUNC_NAME, &WON_POSTPROC_COLORLIMIT_FUNC_SRC},
	{(std::string)WON_UTIL_RANDOM_FUNC_NAME, &WON_UTIL_RANDOM_FUNC_SRC},
	{(std::string)WON_POSTPROC_NOISE_FUNC_NAME, &WON_POSTPROC_NOISE_FUNC_SRC},
	{(std::string)WON_POSTPROC_DITHER_FUNC_NAME, &WON_POSTPROC_DITHER_FUNC_SRC},
};

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

const std::string* won::Defaults::GetShaderSource(const std::string& name)
{
	return nameToSource.at(name);
}

void won::Defaults::LoadShader()
{
	ShaderManager::CreateShader(DEFAULT_SHADER_NAME, WON_DEFAULT_VERTEX_SHADER, WON_DEFAULT_FRAGMENT_SHADER);
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
