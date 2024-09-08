#include "include/WontonEngine/Rendering/ScreenRenderer.h"
#include "include/WontonEngine/Components/Renderer.h"
#include "include/WontonEngine/Components/Transform.h"
#include "glad/glad.h"
#include "include/WontonEngine/Time.h"

void won::priv::ScreenRenderer::Render(const std::vector<std::unique_ptr<Entity>>& entities, const Game& game)
{
	if (camera == nullptr) return;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const std::unique_ptr<Entity>& entity : entities)
	{
		cmp::Renderer* renderer = entity->GetComponent<cmp::Renderer>();
		if (renderer == nullptr) continue;

		Matrix4x4 transformation{1};
		cmp::Transform* transform = entity->GetComponent<cmp::Transform>();
		if (transform != nullptr) transformation = transform->CalculateMatrix();

		renderer->ActivateMaterial();
		Shader shader = renderer->GetMaterial()->GetShader();

		Mesh mesh = renderer->GetMesh();

		// find reserved names
		GLint count;
		glGetProgramiv(shader->progId, GL_ACTIVE_UNIFORMS, &count);

		for (GLint i = 0; i < count; i++)
		{
			GLint size;
			GLenum type;
			
			const GLsizei bufSize = 128;
			GLchar name[bufSize];
			GLsizei length;

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

		renderer->GetMaterial()->Deactivate();

		// reset the active texture
		glActiveTexture(GL_TEXTURE0);
	}
}

void won::priv::ScreenRenderer::SetActiveCamera(cmp::Camera* camera)
{
	this->camera = camera;
}
