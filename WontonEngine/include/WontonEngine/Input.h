#pragma once

#include <unordered_map>
#include "Math/Vector.h"
#include <SDL3/SDL.h>

namespace won
{
	enum class KeyCode
	{
        Key_UNKNOWN = 0,

        Key_RETURN = '\r',
        Key_ESCAPE = '\x1B',
        Key_BACKSPACE = '\b',
        Key_TAB = '\t',
        Key_SPACE = ' ',
        Key_EXCLAIM = '!',
        Key_QUOTEDBL = '"',
        Key_HASH = '#',
        Key_PERCENT = '%',
        Key_DOLLAR = '$',
        Key_AMPERSAND = '&',
        Key_QUOTE = '\'',
        Key_LEFTPAREN = '(',
        Key_RIGHTPAREN = ')',
        Key_ASTERISK = '*',
        Key_PLUS = '+',
        Key_COMMA = ',',
        Key_MINUS = '-',
        Key_PERIOD = '.',
        Key_SLASH = '/',
        Key_0 = '0',
        Key_1 = '1',
        Key_2 = '2',
        Key_3 = '3',
        Key_4 = '4',
        Key_5 = '5',
        Key_6 = '6',
        Key_7 = '7',
        Key_8 = '8',
        Key_9 = '9',
        Key_COLON = ':',
        Key_SEMICOLON = ';',
        Key_LESS = '<',
        Key_EQUALS = '=',
        Key_GREATER = '>',
        Key_QUESTION = '?',
        Key_AT = '@',

        Key_LEFTBRACKET = '[',
        Key_BACKSLASH = '\\',
        Key_RIGHTBRACKET = ']',
        Key_CARET = '^',
        Key_UNDERSCORE = '_',
        Key_BACKQUOTE = '`',
        Key_A = 'a',
        Key_B = 'b',
        Key_C = 'c',
        Key_D = 'd',
        Key_E = 'e',
        Key_F = 'f',
        Key_G = 'g',
        Key_H = 'h',
        Key_I = 'i',
        Key_J = 'j',
        Key_K = 'k',
        Key_L = 'l',
        Key_M = 'm',
        Key_N = 'n',
        Key_O = 'o',
        Key_P = 'p',
        Key_Q = 'q',
        Key_R = 'r',
        Key_S = 's',
        Key_T = 't',
        Key_U = 'u',
        Key_V = 'v',
        Key_W = 'w',
        Key_X = 'x',
        Key_Y = 'y',
        Key_Z = 'z',

        Key_F1 = SDLK_F1,
        Key_F2 = SDLK_F2,
        Key_F3 = SDLK_F3,
        Key_F4 = SDLK_F4,
        Key_F5 = SDLK_F5,
        Key_F6 = SDLK_F6,
        Key_F7 = SDLK_F7,
        Key_F8 = SDLK_F8,
        Key_F9 = SDLK_F9,
        Key_F10 = SDLK_F10,
        Key_F11 = SDLK_F11,
        Key_F12 = SDLK_F12,

        Key_LEFT = SDLK_LEFT,
        Key_UP = SDLK_UP,
        Key_RIGHT = SDLK_RIGHT,
        Key_DOWN = SDLK_DOWN,
	};

	enum class MouseButton
	{
		Button_Left,
		Button_Middle,
		Button_Right
	};

    class Game;

    namespace priv
    {
        class InputUpd
        {
        public:
            static void InputPoll();

            friend class Game;
        };
    }

	class Input
	{
	public:
		static bool GetKey(KeyCode key);
		static bool GetKeyDown(KeyCode key);
		static bool GetKeyUp(KeyCode key);

		static Vector2 GetMousePosition();
		static bool GetMouse(MouseButton button);
		static bool GetMouseDown(MouseButton button);
		static bool GetMouseUp(MouseButton button);
		static Vector2 GetMouseMovement();

        static bool HasQuit();
    private:
        static void Poll();

	private:
		static std::unordered_map<KeyCode, std::pair<bool, bool>> keymap;
		static std::unordered_map<MouseButton, std::pair<bool, bool>> mousemap;
        static Vector2 mousePosition;

        static bool hasQuit;

        friend class priv::InputUpd;
	};
}