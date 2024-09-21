#pragma once

#include <string>
#include "EntityCreator.h"
#include "Vertex.h"
#include <vector>

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
	
		static constexpr char* DEFAULT_SHADER_NAME = "WON_DefaultShader";
		static constexpr char* DEFAULT_MATERIAL_NAME = "WON_DefaultMaterial";
		static constexpr char* BOX_MESH_NAME = "WON_BoxMesh";
		static constexpr char* PLANE_MESH_NAME = "WON_PlaneMesh";
		static constexpr char* UNDEFINED_TEXTURE_NAME = "WON_UndefinedTexture";

	public:
		static void Load(AssetType type);

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
		static const std::string vertexShader;
		static const std::string fragmentShader;
	};
}