#pragma once
//STD headers
#include <functional>

//Library headers

//Coati headers
#include "core/input/definitions/Input.h"

namespace core {
	enum class GamepadButton : unsigned {
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LEFT_BUMPER = 4,
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

	static std::unordered_map<std::string, GamepadButton> StringToGamepadButtonMap = {
		{"A", GamepadButton::A},
		{"B", GamepadButton::B},
		{"X", GamepadButton::X},
		{"Y", GamepadButton::Y},
		{"LEFT_BUMPER", GamepadButton::LEFT_BUMPER},
		{"RIGHT_BUMPER", GamepadButton::RIGHT_BUMPER},
		{"BACK", GamepadButton::BACK},
		{"START", GamepadButton::START},
		{"GUIDE", GamepadButton::GUIDE},
		{"LEFT_THUMB", GamepadButton::LEFT_THUMB},
		{"RIGHT_THUMB", GamepadButton::RIGHT_THUMB},
		{"DPAD_UP", GamepadButton::DPAD_UP},
		{"DPAD_RIGHT", GamepadButton::DPAD_RIGHT},
		{"DPAD_DOWN", GamepadButton::DPAD_DOWN},
		{"DPAD_LEFT", GamepadButton::DPAD_LEFT}
	};

	inline GamepadButton DeserializeGamepadButton(const std::string& key, const std::vector<std::string> modifiers) {
		return StringToGamepadButtonMap.find(key)->second;
	}
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