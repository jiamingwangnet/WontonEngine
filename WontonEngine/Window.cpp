#include "include/WontonEngine/Window.h"
#include <glad/glad.h>
#include "include/WontonEngine/Error.h"
#include <iostream>
#include <cassert>
#include <thread>
#include "include/WontonEngine/Game.h"

won::priv::Window::Window(int width, int height, const std::string& name, WinFlags flags, Color clear, bool vsync, int cwidth, int cheight)
	: width{width}, height{height}, name{name}, clear{clear}, vsync{vsync}, window{nullptr}, flags{flags}, cwidth{cwidth}, cheight{cheight}
{}

int won::priv::Window::GetWidth() const
{
	return width;
}

int won::priv::Window::GetHeight() const
{
	return height;
}

int won::priv::Window::GetContextWidth() const
{
	if (cwidth == -1) return width;
	else return cwidth;
}

int won::priv::Window::GetContextHeight() const
{
	if (cheight == -1) return height;
	else return cheight;
}

std::string won::priv::Window::GetName() const
{
	return name;
}

bool won::priv::Window::IsVsync() const
{
	return vsync;
}

void won::priv::Window::SetClear(Color color)
{
	clear = color;
}

void won::priv::Window::SetVsync(bool vsync)
{
	this->vsync = vsync;
}

void won::priv::Window::Init()
{
	Uint32 windowFlags = SDL_WINDOW_OPENGL;

	if ((unsigned int)flags & (unsigned int)WinFlags::Borderless)
		windowFlags |= (unsigned int)SDL_WINDOW_BORDERLESS;
	if ((unsigned int)flags & (unsigned int)WinFlags::Fullscreen)
		windowFlags |= SDL_WINDOW_FULLSCREEN;
	if((unsigned int)flags & (unsigned int)WinFlags::Invisible)
		windowFlags |= SDL_WINDOW_HIDDEN;
	if ((unsigned int)flags & (unsigned int)WinFlags::Resizable)
		windowFlags |= SDL_WINDOW_RESIZABLE;

	// Set OpenGL version to 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Use core profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow(name.c_str(), width, height, windowFlags);
	if (window == nullptr) Error::ThrowError("Could not create a window.", std::cout, __LINE__, __FILE__);
}

void won::priv::Window::InitContext()
{
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) Error::ThrowError("Could not create an OpenGL context.", std::cout, __LINE__, __FILE__);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		Error::ThrowError("Could not load OpenGL functions.", std::cout, __LINE__, __FILE__);

	int w, h;
	SDL_GetWindowSizeInPixels(window, &w, &h); // returns the actual size determined by OS
	glViewport(0, 0, w, h);
	width = w;
	height = h;

	glClearColor(clear.r / 255.0f, clear.g / 255.0f, clear.b / 255.0f, clear.a / 255.0f);

	SDL_GL_SetSwapInterval((int)vsync);

	// enable depth buffer
	glEnable(GL_DEPTH_TEST);

	// alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

void won::priv::Window::SwapBuffer()
{
	SDL_GL_SwapWindow(window);
}

void won::priv::Window::UpdateWindowSize()
{
	int w, h;
	SDL_GetWindowSizeInPixels(window, &w, &h);
	width = w;
	height = h;
	rdr_hasResized = true;
}
