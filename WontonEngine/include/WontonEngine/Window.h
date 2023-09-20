#pragma once

#include <SDL3/SDL.h>
#include <string>
#include "Color.h"

namespace won
{
	enum class WinFlags
	{
		Invisible = 0b001,
		Fullscreen = 0b010,
		Borderless = 0b100
	};

	namespace priv
	{
		class Window
		{
		public:
			Window(int width, int height, const std::string& name, WinFlags flags, Color clear, bool vsync = true);

			int GetWidth() const;
			int GetHeight() const;
			std::string GetName() const;
			bool IsVsync() const;

			void SetClear(Color color);
			void SetVsync(bool vsync);

			void Init();
			void SwapBuffer();

		private:
			int width;
			int height;
			std::string name;
			Color clear;
			bool vsync;

			SDL_Window* window;
		};
	}
}