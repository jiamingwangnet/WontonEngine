#include "include/WontonEngine/Rendering/Mesh.h"
#include "include/WontonEngine/Error.h"
#include <glad/glad.h>
#include <iostream>
#include <cassert>
#include <thread>
#include "include/WontonEngine/Game.h"

won::priv::IAssetManager<won::priv::MeshBase, won::Mesh> won::MeshManager::assetManager;

won::priv::MeshBase::MeshBase(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices)
	: vertices{std::move(vertices)}, indices{std::move(indices)}, nIndices{(GLsizei)this->indices.size()}
{}

won::priv::MeshBase::MeshBase(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	: vertices{ vertices }, indices{ indices }, nIndices{ (GLsizei)indices.size() }
{}

void won::priv::MeshBase::GenerateMesh()
{
	// TODO: use glBufferSubData to avoid regenerating buffers
	if (vao != 0 || vbo != 0 || ebo != 0) // delete old buffer after modification
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), (const void*)vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), (const void*)indices.data(), GL_STATIC_DRAW);

	// vertex attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

won::Mesh won::MeshManager::CreateMesh(const std::string& name, const std::string& path)
{
	Error::ThrowError("NOT IMPLEMENTED", std::cout, __LINE__, __FILE__);
	return Mesh();
}

won::Mesh won::MeshManager::CreateMesh(const std::string& name, std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices)
{
	assetManager.CreateAsset(name, std::move(vertices), std::move(indices));
	assetManager.GetAsset(name)->GenerateMesh();

	return assetManager.GetAsset(name);
}

won::Mesh won::MeshManager::CreateMesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	assetManager.CreateAsset(name, vertices, indices);
	assetManager.GetAsset(name)->GenerateMesh();

	return assetManager.GetAsset(name);
}

won::Mesh won::MeshManager::GetMesh(const std::string& name)
{
	return assetManager.GetAsset(name);
}
