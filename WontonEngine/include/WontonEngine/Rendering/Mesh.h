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
			MeshBase(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices);
			MeshBase(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

			void GenerateMesh();
		private:
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;

			GLuint vbo = 0;
			GLuint vao = 0;
			GLuint ebo = 0;

			GLsizei nIndices;

			friend class ScreenRenderer;
		};
	}

	using Mesh = priv::MeshBase*;

	class MeshManager
	{
	public:
		static Mesh CreateMesh(const std::string& name, const std::string& path); // load a file
		static Mesh CreateMesh(const std::string& name, std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices);
		static Mesh CreateMesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

		static Mesh GetMesh(const std::string& name);

	private:
		static priv::AssetManagerBase<priv::MeshBase, Mesh> assetManager;
	};
}