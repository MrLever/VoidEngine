#pragma once
//STD Headers
#include <functional>

//Library Headers

//Coati Headers
#include "GenericInput.h"
#include "EngineUtilities.h"

namespace EngineCore {

	enum class MouseButton : unsigned {
		Left = 0,
		Right = 1,
		Middle = 2,
		Thumb_1 = 3,
		Thumb_2 = 4
	};

	class MouseInput : public GenericInput<MouseButton> {
	private:


	public:
		//tors
		MouseInput(MouseButton button, ButtonState state);
		MouseInput(MouseButton button, ButtonState state, EngineUtilities::GameTime timeStamp);
		~MouseInput();

	private:
		//Private Class Members

	public:
		//Public Class Members
		std::size_t Hash() const override;
	};

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