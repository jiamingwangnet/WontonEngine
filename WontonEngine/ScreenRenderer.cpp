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

	// find dirty lights
	dirtyLsize = 0;
	for (int i = 0; i < lsize; i++) // FIXME: broken after switching scenes
	{
		if ((*lights)[i].dirty || IsTransformDirty((*renderables)[lIndexToEIndex[i]]))
		{
			cmp::Transform* transform = ((Entity)lIndexToEntity[i]).GetComponent<cmp::Transform>();
			(*lights)[i].position = transform->GetPosition();
			glm::vec3 forward = (glm::vec3)cmp::Transform::FORWARD;
			(*lights)[i].direction = (Vector3)(transform->GetRotationQuat() * glm::vec3{ forward.x, forward.y, forward.z });

			dirtyLights[dirtyLsize] = i;
			dirtyLsize++;
		}
	}

	Matrix4x4 projection = camera->CalculateProjection();
	Matrix4x4 lookat = camera->CalculateLookAt();
	Vector3 camPos = camera->GetEntity().GetComponent<cmp::Transform>()->GetPosition();
	Matrix4x4 model{ 1.0f };
	Matrix4x4 projview = projection * lookat;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::size_t i = 0; i < rdsize; i++)
	{
		Renderable& renderable = (*renderables)[i];
		if (renderable.material == nullptr || renderable.mesh == nullptr) continue;

		renderable.material->Activate();
		Shader shader = renderable.material->GetShader();

		// could be set for each shader instead each entity
		if (glGetUniformLocation(shader->progId, WON_PROJECTIONMATRIX) != GL_INVALID_INDEX) shader->SetMat4NoThrow(WON_PROJECTIONMATRIX, projection);
		if (glGetUniformLocation(shader->progId, WON_VIEWMATRIX) != GL_INVALID_INDEX) shader->SetMat4NoThrow(WON_VIEWMATRIX, lookat);
		if (glGetUniformLocation(shader->progId, WON_FRAMES) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_FRAMES, Time::GetRenderFrames());
		if (glGetUniformLocation(shader->progId, WON_TIME) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_TIME, (int)Time::GetTime());
		if (glGetUniformLocation(shader->progId, WON_WINDOWWIDTH) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_WINDOWWIDTH, game.GetWidth());
		if (glGetUniformLocation(shader->progId, WON_WINDOWHEIGHT) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_WINDOWHEIGHT, game.GetHeight());
		if (glGetUniformLocation(shader->progId, WON_VIEWPOSITION) != GL_INVALID_INDEX) shader->SetVec3NoThrow(WON_VIEWPOSITION, camPos);
		if (glGetUniformLocation(shader->progId, WON_NUMLIGHTS) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_NUMLIGHTS, (int)lsize);

		// have to set a different model matrix for each object
		bool modelmat = glGetUniformLocation(shader->progId, WON_MODELMATRIX) != GL_INVALID_INDEX;
		bool mvpmat = glGetUniformLocation(shader->progId, WON_MODELVIEWPROJMAT) != GL_INVALID_INDEX;
		bool mvmat = glGetUniformLocation(shader->progId, WON_MODELVIEWMATRIX) != GL_INVALID_INDEX;
		bool nmat = glGetUniformLocation(shader->progId, WON_NORMALMATRIX) != GL_INVALID_INDEX;
		if (modelmat || mvpmat || mvmat || nmat)
		{
			if (IsTransformDirty(renderable))
			{
				renderable.modelMatCache = CalculateMatrix(renderable, model);
				renderable.normalMatCache = glm::mat3{ glm::transpose(glm::inverse((glm::mat4)renderable.modelMatCache)) }; // use viewmodel or model??
			}

			if (modelmat)
				shader->SetMat4NoThrow(WON_MODELMATRIX, renderable.modelMatCache);
			if(mvpmat)
				shader->SetMat4NoThrow(WON_MODELVIEWPROJMAT, projview * renderable.modelMatCache);
			if (mvmat)
				shader->SetMat4NoThrow(WON_MODELVIEWMATRIX, lookat * renderable.modelMatCache);
			if (nmat)
				shader->SetMat3NoThrow(WON_NORMALMATRIX, renderable.normalMatCache);
		}

		for (std::size_t i = 0; i < dirtyLsize; i++)
		{
			std::size_t li = dirtyLights[i];

			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 0]) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 0], (int)(*lights)[li].type);

			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 1]) != GL_INVALID_INDEX) shader->SetVec3NoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 1], (*lights)[li].position);
			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 2]) != GL_INVALID_INDEX) shader->SetVec3NoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 2], (*lights)[li].direction);

			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 3]) != GL_INVALID_INDEX) shader->SetfColorNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 3], (*lights)[li].color);
			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 4]) != GL_INVALID_INDEX) shader->SetFloatNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 4], (*lights)[li].ambientStrength);

			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 5]) != GL_INVALID_INDEX) shader->SetFloatNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 5], (*lights)[li].linear);
			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 6]) != GL_INVALID_INDEX) shader->SetFloatNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 6], (*lights)[li].quadratic);
			
			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 7]) != GL_INVALID_INDEX) shader->SetFloatNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 7], (*lights)[li].cutOff);
			if (glGetUniformLocation(shader->progId, WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 8]) != GL_INVALID_INDEX) shader->SetFloatNoThrow(WON_LIGHT_UNIFORMS_ARRAY[WON_LIGHT_INTERNAL_NPROPERTIES * li + 8], (*lights)[li].outerCutOff);
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
	lIndexToEIndex[lsize] = entityToIndex[entity.GetId()];
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
	if (HasLight(entity))
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

void won::priv::ScreenRenderer::Clear()
{
	entityToIndex.clear();
	indexToEntity.clear();
	lEntityToIndex.clear();
	lIndexToEntity.clear();
	rdsize = 0;
	lsize = 0;
	dirtyLsize = 0;
	for (Renderable& renderable : *renderables)
	{
		renderable = Renderable{};
	}

	for (LightInternal& light : *lights)
	{
		light = LightInternal{};
	}

	for (std::size_t& index : lIndexToEIndex)
	{
		index = 0;
	}

	for (std::size_t& light : dirtyLights)
	{
		light = 0;
	}
}

won::Matrix4x4 won::priv::ScreenRenderer::CalculateMatrix(Renderable& renderable, Matrix4x4& model)
{
	if (renderable.parent.GetId() == INVALID_ENTITY)
		return cmp::Transform::CalculateMatrix(renderable.scale, renderable.position, renderable.rotation, model);
	return CalculateMatrix((*renderables)[entityToIndex[renderable.parent.GetId()]], model) * cmp::Transform::CalculateMatrix(renderable.scale, renderable.position, renderable.rotation, model);
}

bool won::priv::ScreenRenderer::IsTransformDirty(Renderable& renderable)
{
	return renderable.tdirty || (renderable.parent.GetId() != INVALID_ENTITY ? IsTransformDirty((*renderables)[entityToIndex[renderable.parent.GetId()]]) : false);
}
