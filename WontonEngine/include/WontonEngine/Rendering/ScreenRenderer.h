#pragma once

#include "../Components/Camera.h"
#include "../Entity.h"
#include "../Math/Crypto.h"
#include "Renderable.h"
#include <unordered_map>
#include <array>

namespace won
{
	namespace priv
	{
		static constexpr const char* WON_PROJECTIONMATRIX = "won_ProjectionMatrix";
		static constexpr const char* WON_VIEWMATRIX       = "won_ViewMatrix";
		static constexpr const char* WON_MODELMATRIX      = "won_ModelMatrix";
		static constexpr const char* WON_FRAMES           = "won_Frames";
		static constexpr const char* WON_TIME             = "won_Time";
		static constexpr const char* WON_WINDOWWIDTH      = "won_WindowWidth";
		static constexpr const char* WON_WINDOWHEIGHT     = "won_WindowHeight";

		static constexpr unsigned int HASH_WON_PROJECTIONMATRIX = COMPILE_TIME_CRC32_STR_L(WON_PROJECTIONMATRIX, 21);
		static constexpr unsigned int HASH_WON_VIEWMATRIX       = COMPILE_TIME_CRC32_STR_L(WON_VIEWMATRIX, 15);
		static constexpr unsigned int HASH_WON_MODELMATRIX      = COMPILE_TIME_CRC32_STR_L(WON_MODELMATRIX, 16);
		static constexpr unsigned int HASH_WON_FRAMES           = COMPILE_TIME_CRC32_STR_L(WON_FRAMES, 11);
		static constexpr unsigned int HASH_WON_TIME             = COMPILE_TIME_CRC32_STR_L(WON_TIME, 9);
		static constexpr unsigned int HASH_WON_WINDOWWIDTH      = COMPILE_TIME_CRC32_STR_L(WON_WINDOWWIDTH, 16);
		static constexpr unsigned int HASH_WON_WINDOWHEIGHT     = COMPILE_TIME_CRC32_STR_L(WON_WINDOWHEIGHT, 17);

		class ScreenRenderer
		{
		public:
			ScreenRenderer();
			ScreenRenderer(const ScreenRenderer&) = delete;

			void Render(const Game& game);
			void SetActiveCamera(cmp::Camera* camera);

			void CreateRenderable(Entity entity);
			Renderable* RetrieveRenderable(Entity entity);
			bool HasRenderable(Entity entity);
			void EntityDestroyed(Entity entity);
		private:
			cmp::Camera* camera = nullptr;

			std::unique_ptr<std::array<Renderable, MAX_ENTITIES>> renderables;
			std::unordered_map<EntId, std::size_t> entityToIndex{};
			std::unordered_map<std::size_t, EntId> indexToEntity{};
			std::size_t rdsize = 0;
		};
	}
}