#include "include/WontonEngine/Rendering/ScreenRenderer.h"
#include "include/WontonEngine/Components/Renderer.h"
#include "include/WontonEngine/Components/Transform.h"
#include "glad/glad.h"
#include "include/WontonEngine/Time.h"
#include <cassert>

won::priv::ScreenRenderer::ScreenRenderer()
{
	renderables = std::make_unique<std::array<Renderable, MAX_ENTITIES>>();
	lights = std::make_unique<std::array<LightInternal, MAX_LIGHTS>>();
}

void won::priv::ScreenRenderer::Render(const Game& game)
{
	if (camera == nullptr) return;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::size_t i = 0; i < rdsize; i++)
	{
		Renderable& renderable = (*renderables)[i];
		if (renderable.material == nullptr || renderable.mesh == nullptr) continue;

		renderable.material->Activate();
		Shader shader = renderable.material->GetShader();

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
				shader->SetMat4(name, CalculateMatrix(renderable));
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
			case HASH_WON_VIEWPOSITION:
				// TODO: optimise and use global position
				shader->SetVec3(name, camera->GetEntity().GetComponent<cmp::Transform>()->GetLocalPosition());
				break;
			case HASH_WON_NUMLIGHTS:
				shader->SetInt(name, lsize);
				break;
			case HASH_WON_LIGHTS:
				// TODO: optimise by pre-generating strings
				shader->SetFloat(name, 1.0f); // required to detect uniform

				for (std::size_t i = 0; i < lsize; i++)
				{
					shader->SetInt((std::string)WON_LIGHTS + (std::string)"l[" + std::to_string(i) + "].type", (int)(*lights)[i].type);

					shader->SetVec3((std::string)WON_LIGHTS + (std::string)"l[" + std::to_string(i) + "].position", (*lights)[i].position);
					shader->SetVec3((std::string)WON_LIGHTS + (std::string)"l[" + std::to_string(i) + "].direction", (*lights)[i].direction);

					shader->SetColor((std::string)WON_LIGHTS + (std::string)"l[" + std::to_string(i) + "].ambient", (*lights)[i].ambient);
					shader->SetColor((std::string)WON_LIGHTS + (std::string)"l[" + std::to_string(i) + "].diffuse", (*lights)[i].diffuse);
					shader->SetColor((std::string)WON_LIGHTS + (std::string)"l[" + std::to_string(i) + "].specular", (*lights)[i].specular);

					shader->SetFloat((std::string)WON_LIGHTS + (std::string)"l[" + std::to_string(i) + "].smoothness", (*lights)[i].smoothness);

					shader->SetFloat((std::string)WON_LIGHTS + (std::string)"l[" + std::to_string(i) + "].linear", (*lights)[i].linear);
					shader->SetFloat((std::string)WON_LIGHTS + (std::string)"l[" + std::to_string(i) + "].quadratic", (*lights)[i].quadratic);
				}
				break;
			}
		}

		// render mesh
		glBindVertexArray(renderable.mesh->vao);
		glDrawElements(GL_TRIANGLES, renderable.mesh->nIndices, GL_UNSIGNED_INT, 0);

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

void won::priv::ScreenRenderer::CreateLight(Entity entity)
{
	lIndexToEntity[lsize] = entity.GetId();
	lEntityToIndex[entity.GetId()] = lsize;
	lsize++;
}

won::priv::LightInternal* won::priv::ScreenRenderer::RetrieveLight(Entity entity)
{
	assert(lEntityToIndex.find(entity.GetId()) != lEntityToIndex.end());
	return &((*lights)[lEntityToIndex[entity.GetId()]]);
}

bool won::priv::ScreenRenderer::HasLight(Entity entity)
{
	return lEntityToIndex.find(entity.GetId()) != lEntityToIndex.end();
}

void won::priv::ScreenRenderer::EntityDestroyed(Entity entity)
{
	// renderables
	if(HasRenderable(entity))
	{
		std::size_t dindex = entityToIndex[entity.GetId()];
		(*renderables)[dindex] = (*renderables)[rdsize - 1];
		entityToIndex[indexToEntity[rdsize - 1]] = dindex;
		indexToEntity[dindex] = indexToEntity[rdsize - 1];

		entityToIndex.erase(entity.GetId());
		indexToEntity.erase(rdsize - 1);

		rdsize--;
	}

	// lights
	if(HasLight(entity))
	{
		std::size_t dindex = lEntityToIndex[entity.GetId()];
		(*lights)[dindex] = (*lights)[lsize - 1];
		lEntityToIndex[lIndexToEntity[lsize - 1]] = dindex;
		lIndexToEntity[dindex] = lIndexToEntity[lsize - 1];

		lEntityToIndex.erase(entity.GetId());
		lIndexToEntity.erase(lsize - 1);

		lsize--;
	}
}

won::Matrix4x4 won::priv::ScreenRenderer::CalculateMatrix(Renderable& renderable)
{
	if (renderable.parent.GetId() == INVALID_ENTITY) return cmp::Transform::CalculateMatrix(renderable.scale, renderable.position, renderable.rotation);
	return CalculateMatrix((*renderables)[entityToIndex[renderable.parent.GetId()]]) * cmp::Transform::CalculateMatrix(renderable.scale, renderable.position, renderable.rotation);
}
