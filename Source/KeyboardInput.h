#pragma once

#ifdef DELETE
	#undef DELETE
#endif //DELETE 


//STD Headers

//Library Headers

//Coati Headers
#include "GenericInput.h"
#include "EngineUtilities.h"

namespace EngineCore {
	
	//Forward Class declarations

	//Keytype specificication matches GLFW, 
	//which also matches ascii for *most* printed characters
	//See: https://www.glfw.org/docs/latest/group__keys.html
	enum class KeyboardButton : unsigned {
		UNKOWN = 0,
		SPACE = 32,
		APOSTROPHE = 39,
		COMMA = 44,
		MINUS = 45,
		PERIOD = 46,
		FORWARD_SLASH = 47,
		NUM_0 = 48,
		NUM_1 = 49,
		NUM_2 = 50,
		NUM_3 = 51,
		NUM_4 = 52,
		NUM_5 = 53,
		NUM_6 = 54,
		NUM_7 = 55,
		NUM_8 = 56,
		NUM_9 = 57,
		SEMICOLON = 59,
		EQUALS = 61,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LEFT_BRACKET = 91,
		BACKWARD_SLASH = 92,
		RIGHT_BRACKET = 93,
		GRAVE_ACCENT = 96,
		ESC = 256,
		ENTER = 257,
		TAB = 258,
		BACKSPACE = 259,
		INSERT = 260,
		DELETE = 261,
		RIGHT = 262,
		LEFT = 263,
		DOWN = 264,
		UP = 265,
		PAGE_UP = 266,
		PAGE_DOWN = 267,
		HOME = 268,
		END = 269,
		CAPS_LOCK = 280,
		SCORLL_LOCK = 281,
		NUM_LOCK = 282,
		PRINT_SCREEN = 283,
		PAUSE = 284,
		F1 = 290,
		F2= 291,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		NUMPAD_0 = 320,
		NUMPAD_1 = 321,
		NUMPAD_2 = 322,
		NUMPAD_3 = 323,
		NUMPAD_4 = 324,
		NUMPAD_5 = 325,
		NUMPAD_6 = 326,
		NUMPAD_7 = 327,
		NUMPAD_8 = 328,
		NUMPAD_9 = 329,
		NUMPAD_DECIMAL = 330,
		NUMPAD_DIVIDE = 331,
		NUMPAD_MULTIPLY = 332,
		NUMPAD_SUBTRACT = 333,
		NUMPAD_ADD = 334,
		NUMPAD_ENTER = 335,
		NUMPAD_EQUAL = 336,
		LEFT_SHIFT = 340,
		LEFT_CONTROL = 341,
		LEFT_ALT = 342,
		LEFT_SUPER = 343,
		RIGHT_SHIFT = 344,
		RIGHT_CONTROL = 345,
		RIGHT_ALT = 346,
		RIGHT_SUPER = 347,
		MENU = 348
	};

	class KeyboardInput : public GenericInput{
	
	private:

	public:
		//CTORS
		KeyboardInput(KeyboardButton key, ButtonState state);
		KeyboardInput(KeyboardButton key, ButtonState state, EngineUtilities::GameTime time);
		~KeyboardInput();

		bool operator==(const KeyboardInput &other) const;

	private:

	public:
		KeyboardButton GetKeyboardButton() const;
		std::size_t Hash() const override;
	};

	using KeyboardInputPtr = std::shared_ptr<KeyboardInput>;
}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<EngineCore::KeyboardInput> { //Class to define hash function for Keyboard Input
		
		//Hash functor
		std::size_t operator()(const EngineCore::KeyboardInput& t) const {
			return t.Hash();
		}
	
	};
}