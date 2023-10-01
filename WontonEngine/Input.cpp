#include "include/WontonEngine/Input.h"
#include <SDL3/SDL.h>

std::unordered_map<won::KeyCode, std::pair<bool, bool>> won::Input::keymap;
std::unordered_map<won::MouseButton, std::pair<bool, bool>> won::Input::mousemap;
bool won::Input::hasQuit = false;
won::Vector2 won::Input::mousePosition{ 0.0f, 0.0f };
won::Vector2 won::Input::lastMousePosition{ 0.0f, 0.0f };

void won::priv::InputUpd::InputPoll()
{
	Input::Poll();
}

bool won::Input::HasQuit()
{
	return hasQuit;
}

void won::Input::Poll()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
		{
			hasQuit = true;
			break;
		}
		case SDL_EVENT_MOUSE_MOTION:
		{
			lastMousePosition = mousePosition;
			mousePosition[0] = event.motion.x;
			mousePosition[1] = event.motion.y;
			break;
		}
		case SDL_EVENT_KEY_DOWN:
		{
			// keycodes are currently the same as SDL keycodes
			bool before = keymap[(KeyCode)event.key.keysym.sym].first;
			keymap[(KeyCode)event.key.keysym.sym].first = true;
			keymap[(KeyCode)event.key.keysym.sym].second = before;
			break;
		}
		case SDL_EVENT_KEY_UP:
		{
			bool before = keymap[(KeyCode)event.key.keysym.sym].first;
			keymap[(KeyCode)event.key.keysym.sym].first = false;
			keymap[(KeyCode)event.key.keysym.sym].second = before;
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			MouseButton button = MouseButton::Button_Left;
			if (event.button.button == SDL_BUTTON_LEFT)
				button = MouseButton::Button_Left;
			if (event.button.button == SDL_BUTTON_MIDDLE)
				button = MouseButton::Button_Middle;
			if (event.button.button == SDL_BUTTON_RIGHT)
				button = MouseButton::Button_Right;

			bool before = mousemap[button].first;
			mousemap[button].first = true;
			mousemap[button].second = before;

			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_UP:
		{
			MouseButton button = MouseButton::Button_Left;
			if (event.button.button == SDL_BUTTON_LEFT)
				button = MouseButton::Button_Left;
			if (event.button.button == SDL_BUTTON_MIDDLE)
				button = MouseButton::Button_Middle;
			if (event.button.button == SDL_BUTTON_RIGHT)
				button = MouseButton::Button_Right;

			bool before = mousemap[button].first;
			mousemap[button].first = false;
			mousemap[button].second = before;
			break;
		}
		}
	}
}

bool won::Input::GetKey(KeyCode key)
{
	return keymap[key].first;
}

bool won::Input::GetKeyDown(KeyCode key)
{
	return keymap[key] == std::pair{ true, false };
}

bool won::Input::GetKeyUp(KeyCode key)
{
	return keymap[key] == std::pair{ false, true };
}

won::Vector2 won::Input::GetMousePosition()
{
	return mousePosition;
}

bool won::Input::GetMouse(MouseButton button)
{
	return mousemap[button].first;
}

bool won::Input::GetMouseDown(MouseButton button)
{
	return mousemap[button] == std::pair{ true, false };
}

bool won::Input::GetMouseUp(MouseButton button)
{
	return mousemap[button] == std::pair{ false, true };
}

won::Vector2 won::Input::GetMouseMovement()
{
	return mousePosition - lastMousePosition;
}
