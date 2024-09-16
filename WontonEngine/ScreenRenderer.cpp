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

		if (glGetUniformLocation(shader->progId, WON_PROJECTIONMATRIX) != GL_INVALID_INDEX) shader->SetMat4NoThrow(WON_PROJECTIONMATRIX, camera->CalculateProjection());
		if (glGetUniformLocation(shader->progId, WON_VIEWMATRIX) != GL_INVALID_INDEX) shader->SetMat4NoThrow(WON_VIEWMATRIX, camera->CalculateLookAt());
		if (glGetUniformLocation(shader->progId, WON_MODELMATRIX) != GL_INVALID_INDEX) shader->SetMat4NoThrow(WON_MODELMATRIX, CalculateMatrix(renderable));
		if (glGetUniformLocation(shader->progId, WON_FRAMES) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_FRAMES, Time::GetRenderFrames());
		if (glGetUniformLocation(shader->progId, WON_TIME) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_TIME, (int)Time::GetTime());
		if (glGetUniformLocation(shader->progId, WON_WINDOWWIDTH) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_WINDOWWIDTH, game.GetWidth());
		if (glGetUniformLocation(shader->progId, WON_WINDOWHEIGHT) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_WINDOWHEIGHT, game.GetHeight());
		if (glGetUniformLocation(shader->progId, WON_VIEWPOSITION) != GL_INVALID_INDEX) shader->SetVec3NoThrow(WON_VIEWPOSITION, camera->GetEntity().GetComponent<cmp::Transform>()->GetPosition());
		if (glGetUniformLocation(shader->progId, WON_NUMLIGHTS) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_NUMLIGHTS, lsize);

		for (std::size_t i = 0; i < lsize; i++)
		{
			// point light culling
			//if ((*lights)[i].type == LightType::Point)
			//{
			//	//std::cout << (*lights)[i].position.x() << ' ' << (*lights)[i].position.y() << ' ' << (*lights)[i].position.z() << '\n';
			//	glm::vec3 tmp = (glm::vec3)((*lights)[i].position - renderable.position);
			//	float dist = (-(*lights)[i].linear + glm::sqrt((*lights)[i].linear * (*lights)[i].linear - 4 * (*lights)[i].quadratic * CTHRESHOLD)) / (2 * (*lights)[i].quadratic);
			//	if (glm::dot(tmp, tmp) > dist) continue;
			//}

			// dirty culling
			if (!(*lights)[i].dirty && !IsTransformDirty((*renderables)[lIndexToEIndex[i]])) continue;

			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 0]) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 0], (int)(*lights)[i].type);

			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 1]) != GL_INVALID_INDEX) shader->SetVec3NoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 1], (*lights)[i].position);
			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 2]) != GL_INVALID_INDEX) shader->SetVec3NoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 2], (*lights)[i].direction);
	
			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 3]) != GL_INVALID_INDEX) shader->SetfColorNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 3], (*lights)[i].color);
			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 4]) != GL_INVALID_INDEX) shader->SetFloatNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 4], (*lights)[i].ambientStrength);

			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 5]) != GL_INVALID_INDEX) shader->SetFloatNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 5], (*lights)[i].linear);
			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 6]) != GL_INVALID_INDEX) shader->SetFloatNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * i + 6], (*lights)[i].quadratic);
		}

		// render mesh
		glBindVertexArray(renderable.mesh->vao);
		glDrawElements(GL_TRIANGLES, renderable.mesh->nIndices, GL_UNSIGNED_INT, 0);

		renderable.material->Deactivate();

		// reset the active texture
		glActiveTexture(GL_TEXTURE0);
	}

	for (std::size_t i = 0; i < rdsize; i++)
	{
		(*renderables)[i].tdirty = false;
	}
	for (std::size_t i = 0; i < lsize; i++)
	{
		(*lights)[i].dirty = false;
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
	lIndexToEIndex[lsize] = entity.GetId();
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
	// renderables (lights will always have renderables)
	std::size_t dindex = entityToIndex[entity.GetId()];
	(*renderables)[dindex] = (*renderables)[rdsize - 1];
	entityToIndex[indexToEntity[rdsize - 1]] = dindex;
	indexToEntity[dindex] = indexToEntity[rdsize - 1];

	entityToIndex.erase(entity.GetId());
	indexToEntity.erase(rdsize - 1);

	rdsize--;

	// lights
	if(HasLight(entity))
	{
		std::size_t ldindex = lEntityToIndex[entity.GetId()];
		(*lights)[ldindex] = (*lights)[lsize - 1];
		lEntityToIndex[lIndexToEntity[lsize - 1]] = ldindex;
		lIndexToEntity[ldindex] = lIndexToEntity[lsize - 1];

		lIndexToEIndex[ldindex] = dindex;

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

bool won::priv::ScreenRenderer::IsTransformDirty(Renderable& renderable)
{
	return renderable.tdirty || (renderable.parent.GetId() != INVALID_ENTITY ? IsTransformDirty((*renderables)[entityToIndex[renderable.parent.GetId()]]) : false);
}
