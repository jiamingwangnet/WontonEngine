#pragma once

#include "../Components/Camera.h"
#include "../Entity.h"

namespace won
{
	namespace priv
	{
		constexpr char* WON_PROJECTIONMATRIX = "won_ProjectionMatrix";
		constexpr char* WON_VIEWMATRIX       = "won_ViewMatrix";
		constexpr char* WON_MODELMATRIX      = "won_ModelMatrix";
		constexpr char* WON_FRAMES           = "won_Frames";
		constexpr char* WON_TIME             = "won_Time";
		constexpr char* WON_WINDOWWIDTH      = "won_WindowWidth";
		constexpr char* WON_WINDOWHEIGHT     = "won_WindowHeight";

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