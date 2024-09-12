#include "include/WontonEngine/Rendering/ScreenRenderer.h"
#include "include/WontonEngine/Components/Renderer.h"
#include "include/WontonEngine/Components/Transform.h"
#include "glad/glad.h"
#include "include/WontonEngine/Time.h"
#include <cassert>

won::priv::ScreenRenderer::ScreenRenderer()
{
	renderables = std::make_unique<std::array<Renderable, MAX_ENTITIES>>();
}

void won::priv::ScreenRenderer::Render(const Game& game)
{
	if (camera == nullptr) return;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::size_t i = 0; i < rdsize; i++)
	{
		Renderable& renderable = (*renderables)[i];
		if (renderable.material == nullptr || renderable.mesh == nullptr) continue;

		Matrix4x4 transformation{1};
		transformation = cmp::Transform::CalculateMatrix(renderable.scale, renderable.position, renderable.rotation);

		renderable.material->Activate();
		Shader shader = renderable.material->GetShader();

		Mesh mesh = renderable.mesh;

		// find reserved names
		GLint count;
		glGetProgramiv(shader->progId, GL_ACTIVE_UNIFORMS, &count);

		constexpr GLsizei bufSize = 128;
		GLint size;
		GLenum type;
		GLsizei length;
		GLchar name[bufSize];
		
		for (GLint i = 0; i < count; i++)
		{			
			glGetActiveUniform(shader->progId, (GLuint)i, bufSize, &length, &size, &type, name);

			// precalculate values during update phase??
			switch (CRC32_STR(name, length + 1))
			{
			case HASH_WON_PROJECTIONMATRIX:
				shader->SetMat4(name, camera->CalculateProjection());
				break;
			case HASH_WON_VIEWMATRIX:
				shader->SetMat4(name, camera->CalculateLookAt());
				break;
			case HASH_WON_MODELMATRIX:
				shader->SetMat4(name, transformation);
				break;
			case HASH_WON_FRAMES:
				shader->SetInt(name, Time::GetRenderFrames());
				break;
			case HASH_WON_TIME:
				shader->SetInt(name, (int)Time::GetTime());
				break;
			case HASH_WON_WINDOWWIDTH:
				shader->SetInt(name, game.GetWidth());
				break;
			case HASH_WON_WINDOWHEIGHT:
				shader->SetInt(name, game.GetHeight());
				break;
			}
		}

		// render mesh
		glBindVertexArray(mesh->vao);
		glDrawElements(GL_TRIANGLES, mesh->nIndices, GL_UNSIGNED_INT, 0);

		// unbind VAO
		glBindVertexArray(0);

		renderable.material->Deactivate();

		// reset the active texture
		glActiveTexture(GL_TEXTURE0);
	}
}

void won::priv::ScreenRenderer::SetActiveCamera(cmp::Camera* camera)
{
	this->camera = camera;
}

void won::priv::ScreenRenderer::CreateRenderable(Entity entity)
{
	entityToIndex[entity.GetId()] = rdsize;
	indexToEntity[rdsize] = entity.GetId();
	rdsize++;
}

won::priv::Renderable* won::priv::ScreenRenderer::RetrieveRenderable(Entity entity)
{
	assert(entityToIndex.find(entity.GetId()) != entityToIndex.end());
	return &((*renderables)[entityToIndex[entity.GetId()]]);
}

bool won::priv::ScreenRenderer::HasRenderable(Entity entity)
{
	return entityToIndex.find(entity.GetId()) != entityToIndex.end();
}

void won::priv::ScreenRenderer::EntityDestroyed(Entity entity)
{
	std::size_t dindex = entityToIndex[entity.GetId()];
	(*renderables)[dindex] = (*renderables)[rdsize - 1];
	entityToIndex[indexToEntity[rdsize - 1]] = dindex;
	indexToEntity[dindex] = indexToEntity[rdsize - 1];

	entityToIndex.erase(entity.GetId());
	indexToEntity.erase(rdsize - 1);

	rdsize--;
}
