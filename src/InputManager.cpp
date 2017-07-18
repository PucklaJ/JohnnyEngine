#include "../include/InputManager.h"
#include <iostream>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

using namespace std;

namespace Johnny
{
	typedef map<Keys, bool>::iterator mapIt;

	Keys InputManager::convertSDL(unsigned int sdl)
	{
		switch (sdl)
		{
		case SDLK_UNKNOWN: return Keys::UNDEFINED;
		case SDLK_RETURN: return Keys::RETURN;
		case SDLK_ESCAPE: return Keys::ESCAPE;
		case SDLK_BACKSPACE: return Keys::BACKSPACE;
		case SDLK_TAB: return Keys::TAB;
		case SDLK_SPACE: return Keys::SPACE;
		case SDLK_EXCLAIM: return Keys::EXCLAIM;
		case SDLK_QUOTEDBL: return Keys::QUOTEDBL;
		case SDLK_HASH: return Keys::HASH;
		case SDLK_PERCENT: return Keys::PERCENT;
		case SDLK_DOLLAR: return Keys::DOLLAR;
		case SDLK_AMPERSAND: return Keys::AMPERSAND;
		case SDLK_QUOTE: return Keys::QUOTE;
		case SDLK_LEFTPAREN: return Keys::LEFTPAREN;
		case SDLK_RIGHTPAREN: return Keys::RIGHTPAREN;
		case SDLK_ASTERISK: return Keys::ASTERISK;
		case SDLK_PLUS: return Keys::PLUS;
		case SDLK_COMMA: return Keys::COMMA;
		case SDLK_MINUS: return Keys::MINUS;
		case SDLK_PERIOD: return Keys::PERIOD;
		case SDLK_SLASH: return Keys::SLASH;
		case SDLK_0: return Keys::_0;
		case SDLK_1: return Keys::_1;
		case SDLK_2: return Keys::_2;
		case SDLK_3: return Keys::_3;
		case SDLK_4: return Keys::_4;
		case SDLK_5: return Keys::_5;
		case SDLK_6: return Keys::_6;
		case SDLK_7: return Keys::_7;
		case SDLK_8: return Keys::_8;
		case SDLK_9: return Keys::_9;
		case SDLK_COLON: return Keys::COLON;
		case SDLK_SEMICOLON: return Keys::SEMICOLON;
		case SDLK_LESS: return Keys::LESS;
		case SDLK_EQUALS: return Keys::EQUALS;
		case SDLK_GREATER: return Keys::GREATER;
		case SDLK_QUESTION: return Keys::QUESTION;
		case SDLK_AT: return Keys::AT;

		case SDLK_LEFTBRACKET: return Keys::LEFTBRACKET;
		case SDLK_BACKSLASH: return Keys::BACKSLASH;
		case SDLK_RIGHTBRACKET: return Keys::RIGHTBRACKET;
		case SDLK_CARET: return Keys::CARET;
		case SDLK_UNDERSCORE: return Keys::UNDERSCORE;
		case SDLK_BACKQUOTE: return Keys::BACKQUOTE;
		case SDLK_a: return Keys::A;
		case SDLK_b: return Keys::B;
		case SDLK_c: return Keys::C;
		case SDLK_d: return Keys::D;
		case SDLK_e: return Keys::E;
		case SDLK_f: return Keys::F;
		case SDLK_g: return Keys::G;
		case SDLK_h: return Keys::H;
		case SDLK_i: return Keys::I;
		case SDLK_j: return Keys::J;
		case SDLK_k: return Keys::K;
		case SDLK_l: return Keys::L;
		case SDLK_m: return Keys::M;
		case SDLK_n: return Keys::N;
		case SDLK_o: return Keys::O;
		case SDLK_p: return Keys::P;
		case SDLK_q: return Keys::Q;
		case SDLK_r: return Keys::R;
		case SDLK_s: return Keys::S;
		case SDLK_t: return Keys::T;
		case SDLK_u: return Keys::U;
		case SDLK_v: return Keys::V;
		case SDLK_w: return Keys::W;
		case SDLK_x: return Keys::X;
		case SDLK_y: return Keys::Y;
		case SDLK_z: return Keys::Z;
				 
		case SDLK_CAPSLOCK: return Keys::CAPSLOCK;
				
		case SDLK_F1: return Keys::F1;
		case SDLK_F2: return Keys::F2;
		case SDLK_F3: return Keys::F3;
		case SDLK_F4: return Keys::F4;
		case SDLK_F5: return Keys::F5;
		case SDLK_F6: return Keys::F6;
		case SDLK_F7: return Keys::F7;
		case SDLK_F8: return Keys::F8;
		case SDLK_F9: return Keys::F9;
		case SDLK_F10: return Keys::F10;
		case SDLK_F11: return Keys::F11;
		case SDLK_F12: return Keys::F12;
				
		case SDLK_PRINTSCREEN: return Keys::PRINTSCREEN;
		case SDLK_SCROLLLOCK: return Keys::SCROLLLOCK;
		case SDLK_PAUSE: return Keys::PAUSE;
		case SDLK_INSERT: return Keys::INSERT;
		case SDLK_HOME: return Keys::HOME;
		case SDLK_PAGEUP: return Keys::PAGEUP;
		case SDLK_DELETE: return Keys::_DELETE;
		case SDLK_END: return Keys::END;
		case SDLK_PAGEDOWN: return Keys::PAGEDOWN;
		case SDLK_RIGHT: return Keys::RIGHT;
		case SDLK_LEFT: return Keys::LEFT;
		case SDLK_DOWN: return Keys::DOWN;
		case SDLK_UP: return Keys::UP;
				
		case SDLK_NUMLOCKCLEAR: return Keys::NUMLOCKCLEAR;
		case SDLK_KP_DIVIDE: return Keys::KP_DIVIDE;
		case SDLK_KP_MULTIPLY: return Keys::KP_MULTIPLY;
		case SDLK_KP_MINUS: return Keys::KP_MINUS;
		case SDLK_KP_PLUS: return Keys::KP_PLUS;
		case SDLK_KP_ENTER: return Keys::KP_ENTER;
		case SDLK_KP_1: return Keys::KP_1;
		case SDLK_KP_2: return Keys::KP_2;
		case SDLK_KP_3: return Keys::KP_3;
		case SDLK_KP_4: return Keys::KP_4;
		case SDLK_KP_5: return Keys::KP_5;
		case SDLK_KP_6: return Keys::KP_6;
		case SDLK_KP_7: return Keys::KP_7;
		case SDLK_KP_8: return Keys::KP_8;
		case SDLK_KP_9: return Keys::KP_9;
		case SDLK_KP_0: return Keys::KP_0;
		case SDLK_KP_PERIOD: return Keys::KP_PERIOD;
				
		case SDLK_APPLICATION: return Keys::APPLICATION;
		case SDLK_POWER: return Keys::POWER;
		case SDLK_KP_EQUALS: return Keys::KP_POWER;
		case SDLK_F13: return Keys::F13;
		case SDLK_F14: return Keys::F14;
		case SDLK_F15: return Keys::F15;
		case SDLK_F16: return Keys::F16;
		case SDLK_F17: return Keys::F17;
		case SDLK_F18: return Keys::F18;
		case SDLK_F19: return Keys::F19;
		case SDLK_F20: return Keys::F20;
		case SDLK_F21: return Keys::F21;
		case SDLK_F22: return Keys::F22;
		case SDLK_F23: return Keys::F23;
		case SDLK_F24: return Keys::F24;
		case SDLK_EXECUTE: return Keys::EXECUTE;
		case SDLK_HELP: return Keys::HELP;
		case SDLK_MENU: return Keys::MENU;
		case SDLK_SELECT: return Keys::SELECT;
		case SDLK_STOP: return Keys::STOP;
		case SDLK_AGAIN: return Keys::AGAIN;
		case SDLK_UNDO: return Keys::UNDO;
		case SDLK_CUT: return Keys::CUT;
		case SDLK_COPY: return Keys::COPY;
		case SDLK_PASTE: return Keys::PASTE;
		case SDLK_FIND: return Keys::FIND;
		case SDLK_MUTE: return Keys::MUTE;
		case SDLK_VOLUMEUP: return Keys::VOLUMEUP;
		case SDLK_VOLUMEDOWN: return Keys::VOLUMEDOWN;
		case SDLK_KP_COMMA: return Keys::KP_COMMA;
		case SDLK_KP_EQUALSAS400: return Keys::KP_EQUALSAS400;
				 
		case SDLK_ALTERASE: return Keys::ALTERASE;
		case SDLK_SYSREQ: return Keys::SYSREQ;
		case SDLK_CANCEL: return Keys::CANCEL;
		case SDLK_CLEAR: return Keys::CLEAR;
		case SDLK_PRIOR: return Keys::PRIOR;
		case SDLK_RETURN2: return Keys::RETURN2;
		case SDLK_SEPARATOR: return Keys::SEPARATOR;
		case SDLK_OUT: return Keys::_OUT;
		case SDLK_OPER: return Keys::OPER;
		case SDLK_CLEARAGAIN: return Keys::CLEARAGAIN;
		case SDLK_CRSEL: return Keys::CRSEL;
		case SDLK_EXSEL: return Keys::EXSEL;
				 
		case SDLK_KP_00: return Keys::KP_00;
		case SDLK_KP_000: return Keys::KP_000;
		case SDLK_THOUSANDSSEPARATOR: return Keys::THOUSANDSSEPARATOR;
		case SDLK_DECIMALSEPARATOR: return Keys::DECIMALSEPARATOR;
		case SDLK_CURRENCYUNIT: return Keys::CURRENCYUNIT;
		case SDLK_CURRENCYSUBUNIT: return Keys::CURRENCYSUBUNIT;
		case SDLK_KP_LEFTPAREN: return Keys::KP_LEFTPAREN;
		case SDLK_KP_RIGHTPAREN: return Keys::KP_RIGHTPAREN;
		case SDLK_KP_LEFTBRACE: return Keys::KP_LEFTBRACE;
		case SDLK_KP_RIGHTBRACE: return Keys::KP_RIGHTBRACE;
		case SDLK_KP_TAB: return Keys::KP_TAB;
		case SDLK_KP_BACKSPACE: return Keys::KP_BACKSPACE;
		case SDLK_KP_A: return Keys::KP_A;
		case SDLK_KP_B: return Keys::KP_B;
		case SDLK_KP_C: return Keys::KP_C;
		case SDLK_KP_D: return Keys::KP_D;
		case SDLK_KP_E: return Keys::KP_E;
		case SDLK_KP_F: return Keys::KP_F;
		case SDLK_KP_XOR: return Keys::KP_XOR;
		case SDLK_KP_POWER: return Keys::KP_POWER;
		case SDLK_KP_PERCENT: return Keys::KP_PERCENT;
		case SDLK_KP_LESS: return Keys::KP_LESS;
		case SDLK_KP_GREATER: return Keys::KP_GREATER;
		case SDLK_KP_AMPERSAND: return Keys::KP_AMPERSAND;
		case SDLK_KP_DBLAMPERSAND: return Keys::KP_DBLAMPERSAND;
		case SDLK_KP_VERTICALBAR: return Keys::KP_VERTICALBAR;
		case SDLK_KP_DBLVERTICALBAR: return Keys::KP_DBLVERTICALBAR;
		case SDLK_KP_COLON: return Keys::KP_COLON;
		case SDLK_KP_HASH: return Keys::KP_HASH;
		case SDLK_KP_SPACE: return Keys::KP_SPACE;
		case SDLK_KP_AT: return Keys::KP_AT;
		case SDLK_KP_EXCLAM: return Keys::KP_EXCLAM;
		case SDLK_KP_MEMSTORE: return Keys::KP_MEMSTORE;
		case SDLK_KP_MEMRECALL: return Keys::KP_MEMRECALL;
		case SDLK_KP_MEMCLEAR: return Keys::KP_MEMCLEAR;
		case SDLK_KP_MEMADD: return Keys::KP_MEMADD;
		case SDLK_KP_MEMSUBTRACT: return Keys::KP_MEMSUBTRACT;
		case SDLK_KP_MEMMULTIPLY: return Keys::KP_MEMMULTIPLY;
		case SDLK_KP_MEMDIVIDE: return Keys::KP_MEMDIVIDE;
		case SDLK_KP_PLUSMINUS: return Keys::KP_PLUSMINUS;
		case SDLK_KP_CLEAR: return Keys::KP_CLEAR;
		case SDLK_KP_CLEARENTRY: return Keys::KP_CLEARENTRY;
		case SDLK_KP_BINARY: return Keys::KP_BINARY;
		case SDLK_KP_OCTAL: return Keys::KP_OCTAL;
		case SDLK_KP_DECIMAL: return Keys::KP_DECIMAL;
		case SDLK_KP_HEXADECIMAL: return Keys::KP_HEXADECIMAL;
				 
		case SDLK_LCTRL: return Keys::LCTRL;
		case SDLK_LSHIFT: return Keys::LSHIFT;
		case SDLK_LALT: return Keys::LALT;
		case SDLK_LGUI: return Keys::LGUI;
		case SDLK_RCTRL: return Keys::RCTRL;
		case SDLK_RSHIFT: return Keys::RSHIFT;
		case SDLK_RALT: return Keys::RALT;
		case SDLK_RGUI: return Keys::RGUI;
				 
		case SDLK_MODE: return Keys::MODE;
				 
		case SDLK_AUDIONEXT: return Keys::AUDIONEXT;
		case SDLK_AUDIOPREV: return Keys::AUDIOPREV;
		case SDLK_AUDIOSTOP: return Keys::AUDIOSTOP;
		case SDLK_AUDIOPLAY: return Keys::AUDIOPLAY;
		case SDLK_AUDIOMUTE: return Keys::AUDIOMUTE;
		case SDLK_MEDIASELECT: return Keys::MEDIASELECT;
		case SDLK_WWW: return Keys::WWW;
		case SDLK_MAIL: return Keys::MAIL;
		case SDLK_CALCULATOR: return Keys::CALCULATOR;
		case SDLK_COMPUTER: return Keys::COMPUTER;
		case SDLK_AC_SEARCH: return Keys::AC_SEARCH;
		case SDLK_AC_HOME: return Keys::AC_HOME;
		case SDLK_AC_BACK: return Keys::AC_BACK;
		case SDLK_AC_FORWARD: return Keys::AC_FORWARD;
		case SDLK_AC_STOP: return Keys::AC_STOP;
		case SDLK_AC_REFRESH: return Keys::AC_REFRESH;
		case SDLK_AC_BOOKMARKS: return Keys::AC_BOOKMARKS;
				 
		case SDLK_BRIGHTNESSDOWN: return Keys::BRIGHTNESSDOWN;
		case SDLK_BRIGHTNESSUP: return Keys::BRIGHTNESSUP;
		case SDLK_DISPLAYSWITCH: return Keys::DISPLAYSWITCH;
		case SDLK_KBDILLUMTOGGLE: return Keys::KBDILLUMTOGGLE;
		case SDLK_KBDILLUMDOWN: return Keys::KBDILLUMDOWN;
		case SDLK_KBDILLUMUP: return Keys::KBDILLUMUP;
		case SDLK_EJECT: return Keys::EJECT;
		case SDLK_SLEEP: return Keys::SLEEP;

		case SDL_BUTTON_LEFT: return Keys::MS_LEFT;
		case SDL_BUTTON_RIGHT: return Keys::MS_RIGHT;
		case SDL_BUTTON_MIDDLE: return Keys::MS_MIDDLE;
		case SDL_BUTTON_X1: return Keys::MS_X1;
		case SDL_BUTTON_X2: return Keys::MS_X2;
		
		default: return Keys::UNDEFINED;
		}
	}

	InputManager::InputManager()
	{
		m_castsShadows = false;
	}

	InputManager::~InputManager()
	{

	}
	bool InputManager::justPressed(Keys kc)
	{
		bool re = isPressed(kc) && !wasPressed(kc);
		return re;
	}

	bool InputManager::isPressed(Keys kc)
	{
		mapIt it = m_keyMap.find(kc);

		if (it != m_keyMap.end())
		{
			return m_keyMap[kc];
		}

		return false;
	}

	bool InputManager::wasPressed(Keys kc)
	{
		mapIt it = m_previousKeyMap.find(kc);
		if (it != m_previousKeyMap.end())
		{
			return m_previousKeyMap[kc];
		}

		return false;
	}

	bool InputManager::update()
	{
		for (mapIt it = m_keyMap.begin(); it != m_keyMap.end(); it++)
		{
			m_previousKeyMap[it->first] = it->second;
		}

		m_mouse.xrel = m_mouse.yrel = m_mouse.wheel_x = m_mouse.wheel_y = 0;

		return true;
	}

	void InputManager::releaseKey(Keys kc)
	{
		m_keyMap[kc] = false;
	}

	void InputManager::pressKey(Keys kc)
	{
		m_keyMap[kc] = true;
	}

	void InputManager::setMouseCoords(unsigned int x, unsigned int y)
	{
		m_mouse.x = x;
		m_mouse.y = y;
	}

	void InputManager::setMouseWheel(int wheel_x, int wheel_y)
	{
		m_mouse.wheel_x = wheel_x;
		m_mouse.wheel_y = wheel_y;
	}

	void InputManager::setMouseRel(int x, int y)
	{
		m_mouse.xrel = x;
		m_mouse.yrel = y;
	}
}
