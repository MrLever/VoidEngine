#pragma once
//STD headers
#include <functional>

//Library headers

//Coati headers
#include "Input.h"

namespace core {
	enum class GamepadButton : unsigned {
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LEFT_BUMBER = 4,
		RIGHT_BUMPER = 5,
		BACK = 6,
		START = 7,
		GUIDE = 8,
		LEFT_THUMB = 9,
		RIGHT_THUMB = 10,
		DPAD_UP = 11,
		DPAD_RIGHT = 12,
		DPAD_DOWN = 13,
		DPAD_LEFT = 14
	};

	using GamepadInput = Input<GamepadButton>;
}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<core::GamepadInput> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const core::GamepadInput& t) const {
			return t.Hash();
		}

	};
}