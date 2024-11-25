#pragma once

#include <SDL3/SDL.h>
#include <string>
#include "Color.h"

namespace won
{
	enum class WinFlags
	{
		Invisible  = 0b0001,
		Fullscreen = 0b0010,
		Borderless = 0b0100,
		Resizable  = 0b1000,
	};

	namespace priv
	{
		class Window
		{
		public:
			Window(int width, int height, const std::string& name, WinFlags flags, Color clear, bool vsync = true, int cwidth = -1, int cheight = -1);

			int GetWidth() const;
			int GetHeight() const;
			int GetContextWidth() const;
			int GetContextHeight() const;

			std::string GetName() const;
			bool IsVsync() const;

			void SetClear(Color color);
			void SetVsync(bool vsync);

			void Init();
			void InitContext();
			void SwapBuffer();

			void UpdateWindowSize();

		private:
			int width;
			int height;
			int cwidth;
			int cheight;
			std::string name;
			Color clear;
			bool vsync;
			WinFlags flags;

			SDL_Window* window;

			bool rdr_hasResized = false; // rdr means this flag must only be reset by the renderer

			friend class ScreenRenderer;
		};
	}
}