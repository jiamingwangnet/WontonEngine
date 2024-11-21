#include "include/WontonEngine/Rendering/ScreenRenderer.h"
#include "include/WontonEngine/Components/Renderer.h"
#include "include/WontonEngine/Components/Transform.h"
#include "glad/glad.h"
#include "include/WontonEngine/Time.h"
#include <cassert>
#include "include/WontonEngine/Defaults.h"

won::priv::ScreenRenderer::ScreenRenderer()
{
	renderables = std::make_unique<std::array<Renderable, MAX_ENTITIES>>();
	lights = std::make_unique<std::array<LightInternal, MAX_LIGHTS>>();
}

void won::priv::ScreenRenderer::Init(const Window& window)
{
	// generate render quad data
	glGenBuffers(1, &pvbo);
	glGenBuffers(1, &pebo);
	glGenVertexArrays(1, &pvao);

	glBindVertexArray(pvao);

	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(POST_QUAD_VERTS), POST_QUAD_VERTS, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(POST_QUAD_INDICES), POST_QUAD_INDICES, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	downscaleFactorX = (float)window.GetWidth() / targetWidth;
	downscaleFactorY = (float)window.GetHeight() / targetHeight;

	downscalebuffer.Generate(targetWidth, targetHeight, 0, false);
	postprocbuffer.Generate(targetWidth, targetHeight, 0);


	// generate uniform buffers
	staticUniformBuffer = ShaderManager::CreateUniformBuffer(WON_STATICUNIFORMS_NAME, sizeof(Won_StaticUniforms));
	lightUniformBuffer = ShaderManager::CreateUniformBuffer(WON_LIGHTUNIFORMS_NAME, sizeof(Won_LightUniforms));

	staticUniforms.won_WindowWidth = targetWidth;
	staticUniforms.won_WindowHeight = targetHeight;
	staticUniforms.won_DownscaleFactorX = downscaleFactorX;
	staticUniforms.won_DownscaleFactorY = downscaleFactorY;

	UniformDataList datalist;
	passthroughMaterial = MaterialManager::CreateMaterial("WON_RENDERER_PASSTHROUGH_MAT", ShaderManager::CreateShader("WON_RENDERER_PASSTHROUGH_SHADER", Defaults::WON_POST_PROCESSING_VERTEX_SHADER, Defaults::WON_DEFAULT_PASSTHROUGH_FRAGMENT_SHADER), std::move(datalist));
}

void won::priv::ScreenRenderer::Render(const Game& game, Window* window)
{
	if (camera == nullptr) return;

	glViewport(0, 0, targetWidth, targetHeight);

	if (window->rdr_hasResized)
	{
		downscaleFactorX = (float)window->GetWidth() / targetWidth;
		downscaleFactorY = (float)window->GetHeight() / targetHeight;

		// resize buffers
		//glViewport(0, 0, GetScaledWidth(*window), GetScaledHeight(*window));

		//postprocbuffer.Resize(GetScaledWidth(*window), GetScaledHeight(*window));
		//downscalebuffer.Resize(GetScaledWidth(*window), GetScaledHeight(*window));

		if (camera->WillAutoCalcAspect())
		{
			camera->SetAspectRatio((float)window->GetWidth() / (float)window->GetHeight());
		}

		/*staticUniforms.won_WindowWidth = GetScaledWidth(*window);
		staticUniforms.won_WindowHeight = GetScaledHeight(*window);*/
		staticUniforms.won_DownscaleFactorX = downscaleFactorX;
		staticUniforms.won_DownscaleFactorY = downscaleFactorY;
		
		window->rdr_hasResized = false;
	}

	if (camera->IsUsingPost()) postprocbuffer.SetAsTarget();
	else downscalebuffer.SetAsTarget();

	lightUniforms.won_NumLights = lsize;

	// find dirty lights
	for (int i = 0; i < lsize; i++)
	{
		if ((*lights)[i].dirty || IsTransformDirty((*renderables)[lIndexToEIndex[i]]))
		{
			cmp::Transform* transform = ((Entity)lIndexToEntity[i]).GetComponent<cmp::Transform>();
			(*lights)[i].position = transform->GetPosition();
			glm::vec3 forward = (glm::vec3)cmp::Transform::FORWARD;
			(*lights)[i].direction = (Vector3)(transform->GetRotationQuat() * glm::vec3{ forward.x, forward.y, forward.z });

			lightUniforms.won_Lights[i].ambientStrength = (*lights)[i].ambientStrength;
			lightUniforms.won_Lights[i].color = (*lights)[i].color;
			lightUniforms.won_Lights[i].cutOff = (*lights)[i].cutOff;
			lightUniforms.won_Lights[i].direction = glm::vec4{ (glm::vec3)(*lights)[i].direction, 0.0 };
			lightUniforms.won_Lights[i].linear = (*lights)[i].linear;
			lightUniforms.won_Lights[i].outerCutOff = (*lights)[i].outerCutOff;
			lightUniforms.won_Lights[i].position = glm::vec4{ (glm::vec3)(*lights)[i].position, 0.0 };
			lightUniforms.won_Lights[i].quadratic = (*lights)[i].quadratic;
			lightUniforms.won_Lights[i].type = (int)(*lights)[i].type;
		}
	}
	

	staticUniforms.won_Frames = Time::GetRenderFrames();
	staticUniforms.won_Time = Time::GetTime();
	staticUniforms.won_ProjectionMatrix = camera->CalculateProjection();
	staticUniforms.won_ViewMatrix = camera->CalculateLookAt();
	staticUniforms.won_ViewPosition = glm::vec4{ (glm::vec3)camera->GetEntity().GetComponent<cmp::Transform>()->GetPosition(), 0.0f };

	Matrix4x4 projview = staticUniforms.won_ProjectionMatrix * staticUniforms.won_ViewMatrix;
	
	staticUniformBuffer->WriteToBuffer(0, sizeof(Won_StaticUniforms), &staticUniforms);
	lightUniformBuffer->WriteToBuffer(offsetof(Won_LightUniforms, won_NumLights), sizeof(lightUniforms.won_NumLights), &lightUniforms);
	lightUniformBuffer->WriteToBuffer(offsetof(Won_LightUniforms, won_Lights), lightUniforms.won_NumLights * sizeof(LightInternalBase), &lightUniforms.won_Lights);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	for (std::size_t i = 0; i < rdsize; i++)
	{
		Renderable& renderable = (*renderables)[i];
		if (renderable.material == nullptr || renderable.mesh == nullptr) continue;

		renderable.material->Activate();
		Shader shader = renderable.material->GetShader();

		// have to set a different model matrix for each object
		bool modelmat = glGetUniformLocation(shader->progId, WON_MODELMATRIX) != GL_INVALID_INDEX;
		bool mvpmat = glGetUniformLocation(shader->progId, WON_MODELVIEWPROJMAT) != GL_INVALID_INDEX;
		bool mvmat = glGetUniformLocation(shader->progId, WON_MODELVIEWMATRIX) != GL_INVALID_INDEX;
		bool nmat = glGetUniformLocation(shader->progId, WON_NORMALMATRIX) != GL_INVALID_INDEX;
		if (modelmat || mvpmat || mvmat || nmat)
		{
			if (IsTransformDirty(renderable))
			{
				renderable.modelMatCache = CalculateMatrix(renderable);
				renderable.normalMatCache = glm::mat3{ glm::transpose(glm::inverse((glm::mat4)renderable.modelMatCache)) }; // calculate in world space
			}

			if (modelmat)
				shader->SetMat4NoThrow(WON_MODELMATRIX, renderable.modelMatCache);
			if(mvpmat)
				shader->SetMat4NoThrow(WON_MODELVIEWPROJMAT, projview * renderable.modelMatCache);
			if (mvmat)
				shader->SetMat4NoThrow(WON_MODELVIEWMATRIX, staticUniforms.won_ViewMatrix * renderable.modelMatCache);
			if (nmat)
				shader->SetMat3NoThrow(WON_NORMALMATRIX, renderable.normalMatCache);
		}

		// render mesh
		glBindVertexArray(renderable.mesh->vao);
		glDrawElements(GL_TRIANGLES, renderable.mesh->nIndices, GL_UNSIGNED_INT, 0);
		
		renderable.material->Deactivate();
		
		// reset the active texture
		glActiveTexture(GL_TEXTURE0);
	}

	glDisable(GL_DEPTH_TEST);

	// render to post quad
	if (camera->IsUsingPost())
	{
		downscalebuffer.SetAsTarget();

		postprocbuffer.ActivateTexture();
		glBindVertexArray(pvao);

		Material material = camera->GetPostMaterial();
		Shader shader = material->GetShader();

		material->Activate();

		if (glGetUniformLocation(shader->progId, WON_POSTPROCTEXTURE) != GL_INVALID_INDEX) shader->SetIntNoThrow(WON_POSTPROCTEXTURE, postprocbuffer.GetTextureLocation());

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		material->Deactivate();
	}


	glViewport(0, 0, window->GetWidth(), window->GetHeight());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	downscalebuffer.ActivateTexture();
	glBindVertexArray(pvao);

	Shader shader = passthroughMaterial->GetShader();

	passthroughMaterial->Activate();

	if (glGetUniformLocation(shader->progId, "won_DownscaleBufferTexture") != GL_INVALID_INDEX) shader->SetIntNoThrow("won_DownscaleBufferTexture", downscalebuffer.GetTextureLocation());
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	passthroughMaterial->Deactivate();



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

bool won::priv::ScreenRenderer::HasLight(EntId entity)
{
	return lEntityToIndex.find(entity) != lEntityToIndex.end();
}

void won::priv::ScreenRenderer::EntityDestroyed(EntId entity)
{
	// renderables (lights will always have renderables)
	std::size_t dindex = entityToIndex[entity];
	(*renderables)[dindex] = (*renderables)[rdsize - 1];
	entityToIndex[indexToEntity[rdsize - 1]] = dindex;
	indexToEntity[dindex] = indexToEntity[rdsize - 1];

	entityToIndex.erase(entity);
	indexToEntity.erase(rdsize - 1);

	rdsize--;

	// lights
	if (HasLight(entity))
	{
		std::size_t ldindex = lEntityToIndex[entity];
		(*lights)[ldindex] = (*lights)[lsize - 1];
		lEntityToIndex[lIndexToEntity[lsize - 1]] = ldindex;
		lIndexToEntity[ldindex] = lIndexToEntity[lsize - 1];

		lIndexToEIndex[ldindex] = dindex;

		lEntityToIndex.erase(entity);
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
}

won::Matrix4x4 won::priv::ScreenRenderer::CalculateMatrix(Renderable& renderable)
{
	if (renderable.parent.GetId() == INVALID_ENTITY)
		return cmp::Transform::CalculateMatrix(renderable.scale, renderable.position, renderable.rotation);
	return CalculateMatrix((*renderables)[entityToIndex[renderable.parent.GetId()]]) * cmp::Transform::CalculateMatrix(renderable.scale, renderable.position, renderable.rotation);
}

bool won::priv::ScreenRenderer::IsTransformDirty(Renderable& renderable)
{
	return renderable.tdirty || (renderable.parent.GetId() != INVALID_ENTITY ? IsTransformDirty((*renderables)[entityToIndex[renderable.parent.GetId()]]) : false);
}

unsigned int won::priv::ScreenRenderer::GetScaledWidth(const Window& window)
{
	return window.GetWidth() / downscaleFactorX;
}

unsigned int won::priv::ScreenRenderer::GetScaledHeight(const Window& window)
{
	return window.GetHeight() / downscaleFactorY;
}
