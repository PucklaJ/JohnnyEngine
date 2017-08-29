#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>
#include "../include/Actor.h"

namespace Johnny
{
	/* \brief A structure which holds data about the mouse
	 *
	 */
	struct Mouse
	{
		unsigned int x; 	//!< The x coordinate of the screen position of the mouse
		unsigned int y; 	//!< The y coordinate of the screen position of the mouse
		int xrel;			//!< The x coordinate of the relative vector from the last frame to this
		int yrel;       	//!< The y coordinate of the relative vector from the last frame to this
		signed int wheel_x; //!< The amount which the mousewheel was moved on the x-Axis in the last frame
		signed int wheel_y; //!< The amount which the mousewheel was moved on the y-Axis in the last frame
	};

	/* \brief A enum with all keyboardkeys and mousebuttons
	 *
	 */
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

	/* \brief A class which stores all information about input
	 *
	 */
	class InputManager : public Actor
	{
	public:
		/* \breif Converts the SDL keycode to Johnny::Keys
		 * \param key The keycode to convert
		 * \return The keycode converted to Johnny::Keys
		 */
		static Keys convertSDL(unsigned int key);

		InputManager();
		virtual ~InputManager();

		/* \brief Find out wether a key is currently pressed
		 * \param kc The key to query
		 * \return true if the given key is currently pressed
		 *
		 */
		bool isPressed(Keys kc);
		/* \brief Find out wether a key was just pressed
		 * \param kc The key to query
		 * \return true if the given key was just pressed
		 *
		 */
		bool justPressed(Keys kc);

		/* \brief Removes the given key from the map
		 * \param kc The key to remove
		 */
		void releaseKey(Keys kc);
		/* \brief Adds the given key from the map
		 * \param kc The key to add
		 */
		void pressKey(Keys kc);
		/* \brief Sets the mouse screen position
		 * \param x The x coordinate to set
		 * \param y The y coordinate to set
		 */
		void setMouseCoords(unsigned int x, unsigned int y);
		/* \brief Sets the amount which the mousewheel was moved in the last frame
		 * \param wheel_x The x amount
		 * \param wheel_y The y amount
		 */
		void setMouseWheel(int wheel_x, int wheel_y);
		/* \brief Sets the amount of how much the mouse moved relative to the last frame
		 * \param x The x amount
		 * \param y The y amount
		 */
		void setMouseRel(int x, int y);

		/* \brief The update method
		 *
		 *
		 * Sets all keys to not pressed
		 */
		bool update();

		const Mouse& getMouse() const { return m_mouse; }
		
	private:
		std::map<Keys, bool> m_keyMap;         //!< The map which stores the statuses of the keys from this frame
		std::map<Keys, bool> m_previousKeyMap; //!< The map which stores the statuses of the keys from the previouse frame

		/* \brief Wheter a key was pressed in the previous frame
		 * \param kc The ky to query
		 * \return Wether the key was pressed
		 */
		bool wasPressed(Keys kc);			   
		Mouse m_mouse; //!< A instance of the Mouse Struct

	};
}


#endif // INPUTMANAGER_H
