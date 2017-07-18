#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>
#include "../include/Actor.h"

using namespace std;

namespace Johnny
{
	struct Mouse
	{
		unsigned int x;
		unsigned int y;
		int xrel;
		int yrel;
		signed int wheel_x;
		signed int wheel_y;
	};

	enum class Keys
	{
		UNDEFINED,
		RETURN,
		ESCAPE,
		BACKSPACE,
		TAB,
		SPACE,
		EXCLAIM,
		QUOTEDBL,
		HASH,
		PERCENT,
		DOLLAR,
		AMPERSAND,
		QUOTE,
		LEFTPAREN,
		RIGHTPAREN,
		ASTERISK,
		PLUS,
		COMMA,
		MINUS,
		PERIOD,
		SLASH,
		_0,
		_1,
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,
		COLON,
		SEMICOLON,
		LESS,
		EQUALS,
		GREATER,
		QUESTION,
		AT,
		LEFTBRACKET,
		BACKSLASH,
		RIGHTBRACKET,
		CARET,
		UNDERSCORE,
		BACKQUOTE,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		CAPSLOCK,

		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,

		PRINTSCREEN,
		SCROLLLOCK,
		PAUSE,
		INSERT,
		HOME,
		PAGEUP,
		_DELETE,
		END,
		PAGEDOWN,
		RIGHT,
		LEFT,
		DOWN,
		UP,

		NUMLOCKCLEAR,
		KP_DIVIDE,
		KP_MULTIPLY,
		KP_MINUS,
		KP_PLUS,
		KP_ENTER,
		KP_1,
		KP_2,
		KP_3,
		KP_4,
		KP_5,
		KP_6,
		KP_7,
		KP_8,
		KP_9,
		KP_0,
		KP_PERIOD,

		APPLICATION,
		POWER,
		KP_EQUALS,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,
		EXECUTE,
		HELP,
		MENU,
		SELECT,
		STOP,
		AGAIN,
		UNDO,
		CUT,
		COPY,
		PASTE,
		FIND,
		MUTE,
		VOLUMEUP,
		VOLUMEDOWN,
		KP_COMMA,
		KP_EQUALSAS400,

		ALTERASE,
		SYSREQ,
		CANCEL,
		CLEAR,
		PRIOR,
		RETURN2,
		SEPARATOR,
		_OUT,
		OPER,
		CLEARAGAIN,
		CRSEL,
		EXSEL,

		KP_00,
		KP_000,
		THOUSANDSSEPARATOR,
		DECIMALSEPARATOR,
		CURRENCYUNIT,
		CURRENCYSUBUNIT,
		KP_LEFTPAREN,
		KP_RIGHTPAREN,
		KP_LEFTBRACE,
		KP_RIGHTBRACE,
		KP_TAB,
		KP_BACKSPACE,
		KP_A,
		KP_B,
		KP_C,
		KP_D,
		KP_E,
		KP_F,
		KP_XOR,
		KP_POWER,
		KP_PERCENT,
		KP_LESS,
		KP_GREATER,
		KP_AMPERSAND,
		KP_DBLAMPERSAND,
		KP_VERTICALBAR,
		KP_DBLVERTICALBAR,
		KP_COLON,
		KP_HASH,
		KP_SPACE,
		KP_AT,
		KP_EXCLAM,
		KP_MEMSTORE,
		KP_MEMRECALL,
		KP_MEMCLEAR,
		KP_MEMADD,
		KP_MEMSUBTRACT,
		KP_MEMMULTIPLY,
		KP_MEMDIVIDE,
		KP_PLUSMINUS,
		KP_CLEAR,
		KP_CLEARENTRY,
		KP_BINARY,
		KP_OCTAL,
		KP_DECIMAL,
		KP_HEXADECIMAL,

		LCTRL,
		LSHIFT,
		LALT,
		LGUI,
		RCTRL,
		RSHIFT,
		RALT,
		RGUI,

		MODE,

		AUDIONEXT,
		AUDIOPREV,
		AUDIOSTOP,
		AUDIOPLAY,
		AUDIOMUTE,
		MEDIASELECT,
		WWW,
		MAIL,
		CALCULATOR,
		COMPUTER,
		AC_SEARCH,
		AC_HOME,
		AC_BACK,
		AC_FORWARD,
		AC_STOP,
		AC_REFRESH,
		AC_BOOKMARKS,

		BRIGHTNESSDOWN,
		BRIGHTNESSUP,
		DISPLAYSWITCH,
		KBDILLUMTOGGLE,
		KBDILLUMDOWN,
		KBDILLUMUP,
		EJECT,
		SLEEP,

		// Mouse Buttons
		MS_LEFT,
		MS_RIGHT,
		MS_MIDDLE,
		MS_X1,
		MS_X2
	};

	class InputManager : public Actor
	{
	public:
		static Keys convertSDL(unsigned int);

		InputManager();
		virtual ~InputManager();

		bool isPressed(Keys kc);
		bool justPressed(Keys kc);

		void releaseKey(Keys kc);
		void pressKey(Keys kc);
		void setMouseCoords(unsigned int x, unsigned int y);
		void setMouseWheel(int wheel_x, int wheel_y);
		void setMouseRel(int x, int y);

		bool update();

		const Mouse& getMouse()
		{
			return m_mouse;
		}

	protected:

	private:
		map<Keys, bool> m_keyMap;
		map<Keys, bool> m_previousKeyMap;

		bool wasPressed(Keys kc);
		Mouse m_mouse;

	};
}


#endif // INPUTMANAGER_H
