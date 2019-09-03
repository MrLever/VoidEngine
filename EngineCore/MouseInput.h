#pragma once
//STD Headers
#include <functional>

//Library Headers

//Coati Headers
#include "Input.h"
#include "EngineUtilities.h"

namespace EngineCore {

	enum class MouseButton : unsigned {
		LEFT = 0,
		RIGHT = 1,
		MIDDLE = 2,
		THUMB_1 = 3,
		THUMB_2 = 4
	};

	using MouseInput = Input<MouseButton>;

}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<EngineCore::MouseInput> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const EngineCore::MouseInput& t) const {
			return t.Hash();
		}

	};
}