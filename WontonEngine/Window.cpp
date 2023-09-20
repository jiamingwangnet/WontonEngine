#include "include/WontonEngine/Window.h"
#include <glad/glad.h>

won::priv::Window::Window(int width, int height, const std::string& name, WinFlags flags, Color clear, bool vsync)
	: width{width}, height{height}, name{name}, clear{clear}, vsync{vsync}, window{nullptr}, flags{flags}
{}

int won::priv::Window::GetWidth() const
{
	return width;
}

int won::priv::Window::GetHeight() const
{
	return height;
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

	// Set OpenGL version to 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Use core profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow(name.c_str(), width, height, windowFlags);
	if (window == nullptr) throw std::exception{ "ERROR: Could not create a window." };

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) throw std::exception{ "ERROR: Could not create an OpenGL context." };

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		throw std::exception{ "ERROR: Could not load OpenGL functions." };

	glClearColor(clear.r / 255.0f, clear.g / 255.0f, clear.b / 255.0f, clear.a / 255.0f);

	if (vsync) SDL_GL_SetSwapInterval(0);

	// alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void won::priv::Window::SwapBuffer()
{
	SDL_GL_SwapWindow(window);
}
