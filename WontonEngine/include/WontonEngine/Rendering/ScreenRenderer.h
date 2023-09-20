#pragma once

#include "../Components/Camera.h"

namespace won
{
	namespace priv
	{
		class ScreenRenderer
		{
		public:
			void Render();
			void SetActiveCamera(cmp::Camera* camera);

		private:
			cmp::Camera* camera = nullptr;
		};
	}
}