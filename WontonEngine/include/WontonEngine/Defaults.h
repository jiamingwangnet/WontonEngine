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
			UndefinedTexture
		};
	
		static constexpr char* DEFAULT_SHADER_NAME = "WON_DefaultShader";
		static constexpr char* DEFAULT_MATERIAL_NAME = "WON_DefaultMaterial";
		static constexpr char* BOX_MESH_NAME = "WON_BoxMesh";
		static constexpr char* UNDEFINED_TEXTURE_NAME = "WON_UndefinedTexture";

	public:
		static void Load(AssetType type);

	private:
		static void LoadShader();
		static void LoadMaterial();
		static void LoadBoxMesh();
		static void LoadUndefinedTexture();

	public:
		class Box : public EntityCreator
		{
		private:
			friend class Game;
			void Create(Entity& entity) const override;
		};

	private:
		static const std::vector<Vertex> box_vertices;
		static const std::vector<unsigned int> box_indices;
		static const std::string vertexShader;
		static const std::string fragmentShader;
	};
}