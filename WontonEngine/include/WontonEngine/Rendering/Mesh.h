#pragma once

#include <vector>
#include "../Vertex.h"
#include "ScreenRenderer.h"
#include <glad/glad.h>
#include <string>
#include "../AssetManagerBase.h"

namespace won
{
	namespace priv
	{
		class MeshBase
		{
		public:
			MeshBase(const std::vector<Vertex>&& vertices, const std::vector<unsigned int>&& indices);

			void GenerateMesh();
		private:
			GLuint vbo;
			GLuint vao;
			GLuint ebo;

			friend class ScreenRenderer;
		};
	}

	using Mesh = priv::MeshBase*;

	class MeshManager
	{
	public:
		static Mesh CreateMesh(const std::string& name, const std::string& path); // load a file
		static Mesh CreateMesh(const std::string& name, const std::vector<Vertex>&& vertices, const std::vector<unsigned int>&& indices);

		static Mesh GetMesh(const std::string& name);

	private:
		static priv::AssetManagerBase<priv::MeshBase, Mesh> assetManager;
	};
}