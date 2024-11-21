#pragma once

#include <string>
#include "EntityCreator.h"
#include "Vertex.h"
#include <vector>
#include <unordered_map>

namespace won
{
	class Defaults
	{
	public:
		enum class AssetType
		{
			All,
			DefaultShader,
			DefaultMaterial,
			BoxMesh,
			PlaneMesh,
			UndefinedTexture
		};
	
		static constexpr const char* DEFAULT_SHADER_NAME = "WON_DefaultShader";
		static constexpr const char* DEFAULT_MATERIAL_NAME = "WON_DefaultMaterial";
		static constexpr const char* BOX_MESH_NAME = "WON_BoxMesh";
		static constexpr const char* PLANE_MESH_NAME = "WON_PlaneMesh";
		static constexpr const char* UNDEFINED_TEXTURE_NAME = "WON_UndefinedTexture";


		static constexpr const char* WON_LIGHTING_FUNC_NAME = "WON_LIGHTING_FUNCTIONS";
		static constexpr const char* WON_POSTPROC_PIXELATE_FUNC_NAME = "WON_POSTPROC_PIXELATE";
		static constexpr const char* WON_POSTPROC_COLORLIMIT_FUNC_NAME = "WON_POSTPROC_COLOR_LIMITER";
		static constexpr const char* WON_UTIL_RANDOM_FUNC_NAME = "WON_UTILITY_RANDOM";
		static constexpr const char* WON_POSTPROC_NOISE_FUNC_NAME = "WON_POSTPROC_NOISE";
		static constexpr const char* WON_POSTPROC_DITHER_FUNC_NAME = "WON_POSTPROC_DITHER";

		static const std::string WON_LIGHTING_FUNC_SRC;
		static const std::string WON_POSTPROC_PIXELATE_FUNC_SRC;
		static const std::string WON_POSTPROC_COLORLIMIT_FUNC_SRC;
		static const std::string WON_UTIL_RANDOM_FUNC_SRC;
		static const std::string WON_POSTPROC_NOISE_FUNC_SRC;
		static const std::string WON_POSTPROC_DITHER_FUNC_SRC;


		static const std::string WON_POST_PROCESSING_VERTEX_SHADER;
		static const std::string WON_DEFAULT_PASSTHROUGH_FRAGMENT_SHADER;

		static const std::string WON_DEFAULT_VERTEX_SHADER;
		static const std::string WON_DEFAULT_FRAGMENT_SHADER;

	public:
		static void Load(AssetType type);
		static const std::string* GetShaderSource(const std::string& name);

	private:
		static void LoadShader();
		static void LoadMaterial();
		static void LoadBoxMesh();
		static void LoadPlaneMesh();
		static void LoadUndefinedTexture();

	public:
		class Box : public EntityCreator
		{
		private:
			friend class Game;
			void Create(Entity& entity) const override;
		};

		class Plane : public EntityCreator
		{
		private:
			friend class Game;
			void Create(Entity& entity) const override;
		};

		class PointLight : public EntityCreator
		{
		private:
			friend class Game;
			void Create(Entity& entity) const override;
		};

		class DirectionalLight : public EntityCreator
		{
		private:
			friend class Game;
			void Create(Entity& entity) const override;
		};

		class SpotLight : public EntityCreator
		{
		private:
			friend class Game;
			void Create(Entity& entity) const override;
		};

	private:
		static const std::vector<Vertex> box_vertices;
		static const std::vector<unsigned int> box_indices;
		static const std::vector<Vertex> plane_vertices;
		static const std::vector<unsigned int> plane_indices;
		static const std::unordered_map<std::string, const std::string*> nameToSource;
	};
}