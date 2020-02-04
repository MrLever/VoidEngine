#pragma once
//STD Headers
#include <functional>

//Library Headers

//Coati Headers
#include "Input.h"

namespace core {

	enum class MouseButton : unsigned {
		LEFT = 0,
		RIGHT = 1,
		MIDDLE = 2,
		THUMB_1 = 3,
		THUMB_2 = 4
	};

	using MouseInput = Input<MouseButton>;

	static std::unordered_map<std::string, MouseButton> StringToMouseButtonMap = {
		{"LEFT", MouseButton::LEFT},
		{"RIGHT", MouseButton::RIGHT},
		{"MIDDLE", MouseButton::MIDDLE},
		{"THUMB_1", MouseButton::THUMB_1},
		{"THUMB_2", MouseButton::THUMB_2}
	};

	inline MouseButton DeserializeMouseButton(const std::string& key, const std::vector<std::string> modifiers) {
		return StringToMouseButtonMap.find(key)->second;
	}

}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<core::MouseInput> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const core::MouseInput& t) const {
			return t.Hash();
		}

	};
}