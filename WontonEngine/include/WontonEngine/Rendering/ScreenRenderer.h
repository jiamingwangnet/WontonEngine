#pragma once

#include "../Components/Camera.h"
#include "../Entity.h"
#include "../Math/Crypto.h"
#include "Renderable.h"
#include <unordered_map>
#include <array>
#include "Lighting.h"
#include <utility>
#include "../ThreadPool.h"
#include "../Window.h"

namespace won
{
	namespace priv
	{
		static constexpr float POST_QUAD_VERTS[] =
		{
			 1.0f,  1.0f, 	1.0f, 1.0f,// top right
			 1.0f, -1.0f,	1.0f, 0.0f,// bottom right
			-1.0f, -1.0f,	0.0f, 0.0f,// bottom left
			-1.0f,  1.0f,	0.0f, 1.0f,// top left 
		};

		static constexpr int POST_QUAD_INDICES[] =
		{
			0, 1, 3,
			1, 2, 3,
		};

		static constexpr const char* WON_PROJECTIONMATRIX = "won_ProjectionMatrix";
		static constexpr const char* WON_VIEWMATRIX       = "won_ViewMatrix";
		static constexpr const char* WON_FRAMES           = "won_Frames";
		static constexpr const char* WON_TIME             = "won_Time";
		static constexpr const char* WON_WINDOWWIDTH      = "won_WindowWidth";
		static constexpr const char* WON_WINDOWHEIGHT     = "won_WindowHeight";
		static constexpr const char* WON_NUMLIGHTS	      = "won_NumLights";
		static constexpr const char* WON_LIGHTS			  = "won_Lights";
		static constexpr const char* WON_VIEWPOSITION     = "won_ViewPosition";
		static constexpr const char* WON_POSTPROCTEXTURE = "won_PostProcTexture";

		
		static constexpr const char* WON_STATICUNIFORMS_NAME = "Won_StaticUniforms";
		static constexpr const char* WON_LIGHTUNIFORMS_NAME = "Won_LightUniforms";

		static constexpr const char* WON_MODELMATRIX = "won_ModelMatrix";
		static constexpr const char* WON_MODELVIEWPROJMAT = "won_ModelViewProjMatrix";
		static constexpr const char* WON_MODELVIEWMATRIX  = "won_ModelViewMatrix";
		static constexpr const char* WON_NORMALMATRIX     = "won_NormalMatrix";


		class ScreenRenderer
		{
		private:
			PACK(struct Won_StaticUniforms
			{
				                                       // incremental size       offset
				Matrix4x4 won_ProjectionMatrix{1.0f};  // 16                     0
												       // 32					 16
												       // 48					 32
												       // 64					 48
				Matrix4x4 won_ViewMatrix{1.0f};        // 80					 64
				                                       // 96					 80
												       // 112					 96
												       // 128					 112
				Vector4 won_ViewPosition;		       // 144					 128
				int won_Frames;					       // 148					 144
				int won_Time;                          // 152					 148
				int won_WindowWidth;                   // 156					 152
				int won_WindowHeight;                  // 160					 156
			}) staticUniforms{};

			PACK(struct Won_LightUniforms
			{
				int won_NumLights;
				char _padding00[12];

				LightInternalBase won_Lights[MAX_LIGHTS];
			}) lightUniforms{};

		public:
			ScreenRenderer();
			ScreenRenderer(const ScreenRenderer&) = delete;

			void Init(const Window& window);
			void Render(const Game& game, Window* window);
			void SetActiveCamera(cmp::Camera* camera);

			void CreateRenderable(Entity entity);
			Renderable* RetrieveRenderable(Entity entity);
			bool HasRenderable(Entity entity);

			void CreateLight(Entity entity);
			LightInternal* RetrieveLight(Entity entity);
			bool HasLight(EntId entity);

			void EntityDestroyed(EntId entity);
			void Clear();

		private:
			won::Matrix4x4 CalculateMatrix(Renderable& renderable);
			bool IsTransformDirty(Renderable& renderable);

		private:
			cmp::Camera* camera = nullptr;

			std::unique_ptr<std::array<Renderable, MAX_ENTITIES>> renderables; // use vector instead?
			std::unordered_map<EntId, std::size_t> entityToIndex{};
			std::unordered_map<std::size_t, EntId> indexToEntity{};
			std::size_t rdsize = 0;
			
			std::unique_ptr<std::array<LightInternal, MAX_LIGHTS>> lights; // abstract into new datatype? 
			std::unordered_map<EntId, std::size_t> lEntityToIndex{};
			std::unordered_map<std::size_t, EntId> lIndexToEntity{};
			std::size_t lsize = 0;

			std::array<std::size_t, MAX_LIGHTS> lIndexToEIndex; // gives the index to the renderable not entity ID

			// post processing

			// screen quad
			unsigned int pvao;
			unsigned int pvbo;
			unsigned int pebo;

			unsigned int fbo;
			unsigned int rtex; // render texture
			unsigned int rbo; // render buffer for stencil and depth

			UniformBuffer staticUniformBuffer = nullptr;
			UniformBuffer lightUniformBuffer = nullptr;
		};
	}
}