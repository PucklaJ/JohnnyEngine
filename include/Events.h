#ifndef EVENTS_H
#define EVENTS_H
#include "InputManager.h"
#include "JoystickListenerEnums.h"

namespace Johnny
{
	enum class EventType
	{
		Quit,
		WindowEvent,
		SysWMEvent,
		KeyDown,
		KeyUp,
		TextEditing,
		TextInput,
		KeyMapChanged,
		MouseMotion,
		MouseButtonDown,
		MouseButtonUp,
		MouseWheel,
		JoyAxisMotion,
		JoyBallMotion,
		JoyHatMotion,
		JoyButtonDown,
		JoyButtonUp,
		JoyDeviceAdded,
		JoyDeviceRemoved,
		ControllerAxisMotion,
		ControllerButtonDown,
		ControllerButtonUp,
		ControllerDeviceAdded,
		ControllerDeviceRemoved,
		ControllerDeviceRemapped,
		FingerDown,
		FingerUp,
		FingerMotion,
		DollarGesture,
		DollarRecord,
		MultiGesture,
		ClipboardUpdate,
		DropFile,
		DropText,
		DropBegin,
		DropComplete,
		AudioDeviceAdded,
		AudioDeviceRemoved,
		RenderTargetsReset,
		RenderDeviceReset,
		UserEvent,
		Undefined
	};

	enum class WindowEventType
	{
		Shown,
		Hidden,
		Exposed,
		Moved,
		Resized,
		SizeChanged,
		Minimized,
		Maximized,
		Restored,
		Enter,
		Leave,
		FocusGained,
		FocusLost,
		Close,
		TakeFocus,
		HitTest,
		Undefined
	};

    class CommonEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
    };
    
    class WindowEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        unsigned int windowID;
        WindowEventType event;
        int data1;
        int data2;
    };
    
    class KeyboardEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        unsigned int windowID;
        unsigned char state;
        unsigned char repeat;
        Keys key;
    };

#define TEXTEDITINGEVENT_TEXT_SIZE (32)

    class TextEditingEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        unsigned int windowID;
        char text[TEXTEDITINGEVENT_TEXT_SIZE];
        int start;
        int length;
    };
    
#define TEXTINPUTEVENT_TEXT_SIZE TEXTEDITINGEVENT_TEXT_SIZE
    
    class TextInputEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        unsigned int windowID;
        char text[TEXTINPUTEVENT_TEXT_SIZE];
    };
    
    class MouseMotionEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        unsigned int windowID;
        unsigned int which;
        unsigned int state;
        int x;
        int y;
        int xrel;
        int yrel;
    };
    
    class MouseButtonEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        unsigned int windowID;
        unsigned int which;
        Keys button;
        unsigned char state;
        unsigned char clicks;
        int x;
        int y;
    };
    
    class MouseWheelEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        unsigned int windowID;
        unsigned int which;
        int x;
        int y;
        unsigned int direction;
    };
    
    class JoyAxisEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        int which;
        Axis axis;
        short value;
    };
    
    class JoyBallEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        int which;
        unsigned char ball;
        short xrel;
        short yrel;
    };
    
    class JoyHatEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        int which;
        unsigned char hat;
        unsigned char value;
    };
    
    class JoyButtonEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        int which;
        Buttons button;
        unsigned char state;
    };
    
    class JoyDeviceEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        int which;
    };
    
    class ControllerAxisEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        int which;
        Axis axis;
        short value;
    };
    
    class ControllerButtonEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        int which;
        Buttons button;
        unsigned char state;
    };
    
    class ControllerDeviceEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        int which;
    };
    
    class AudioDeviceEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        unsigned int which;
        unsigned char iscapture;
    };
    
    class QuitEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
    };
    
    class UserEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        unsigned int windowID;
        int code;
        void* data1;
        void* data2;
    };
    
    struct SysWMmsg;
    
    class SysWMEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        SysWMmsg* msg;
    };
    
    class TouchFingerEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        long touchID;
        long fingerID;
        float x;
        float y;
        float dx;
        float dy;
        float pressure;
    };
    
    class MultiGestureEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        long touchID;
        float dTheta;
        float dDist;
        float x;
        float y;
        unsigned short numFingers;
    };
    
    class DollarGestureEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        long touchID;
        long gestureID;
        unsigned int numFingers;
        float error;
        float x;
        float y;
    };
    
    class DropEvent
    {
    public:
        EventType type;
        unsigned int timestamp;
        char* file;
        unsigned int windowID;
    };
    
    class Event
    {
    public:
        EventType type;
        CommonEvent common;         /**< Common event data */
        WindowEvent window;         /**< Window event data */
        KeyboardEvent key;          /**< Keyboard event data */
        TextEditingEvent edit;      /**< Text editing event data */
        TextInputEvent text;        /**< Text input event data */
        MouseMotionEvent motion;    /**< Mouse motion event data */
        MouseButtonEvent button;    /**< Mouse button event data */
        MouseWheelEvent wheel;      /**< Mouse wheel event data */
        JoyAxisEvent jaxis;         /**< Joystick axis event data */
        JoyBallEvent jball;         /**< Joystick ball event data */
        JoyHatEvent jhat;           /**< Joystick hat event data */
        JoyButtonEvent jbutton;     /**< Joystick button event data */
        JoyDeviceEvent jdevice;     /**< Joystick device change event data */
        ControllerAxisEvent caxis;      /**< Game Controller axis event data */
        ControllerButtonEvent cbutton;  /**< Game Controller button event data */
        ControllerDeviceEvent cdevice;  /**< Game Controller device event data */
        AudioDeviceEvent adevice;   /**< Audio device event data */
        QuitEvent quit;             /**< Quit request event data */
        UserEvent user;             /**< Custom event data */
        SysWMEvent syswm;           /**< System dependent window event data */
        TouchFingerEvent tfinger;   /**< Touch finger event data */
        MultiGestureEvent mgesture; /**< Gesture event data */
        DollarGestureEvent dgesture; /**< Gesture event data */
        DropEvent drop;
    };
}

#endif
