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
			
			const GLsizei bufSize = 32;
			GLchar name[bufSize];
			GLsizei length;

			glGetActiveUniform(shader->progId, (GLuint)i, bufSize, &length, &size, &type, name);

			if (strcmp((const char*)name, WON_PROJECTIONMATRIX) == 0)
			{
				shader->SetMat4(name, camera->CalculateProjection());
			}
			else if (strcmp((const char*)name, WON_VIEWMATRIX) == 0)
			{
				shader->SetMat4(name, camera->CalculateLookAt());
			}
			else if (strcmp((const char*)name, WON_MODELMATRIX) == 0)
			{
				shader->SetMat4(name, transformation);
			}
			else if (strcmp((const char*)name, WON_FRAMES) == 0)
			{
				shader->SetInt(name, Time::GetRenderFrames());
			}
			else if (strcmp((const char*)name, WON_TIME) == 0)
			{
				shader->SetInt(name, (int)Time::GetTime());
			}
			else if (strcmp((const char*)name, WON_WINDOWWIDTH) == 0)
			{
				shader->SetInt(name, game.GetWidth());
			}
			else if (strcmp((const char*)name, WON_WINDOWHEIGHT) == 0)
			{
				shader->SetInt(name, game.GetHeight());
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
