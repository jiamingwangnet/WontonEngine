#pragma once

#include "../Components/Camera.h"
#include "../Entity.h"
#include "../Math/Crypto.h"

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
			void Render(const std::vector<std::unique_ptr<Entity>>& entities, const Game& game);
			void SetActiveCamera(cmp::Camera* camera);

		private:
			cmp::Camera* camera = nullptr;
		};
	}
}