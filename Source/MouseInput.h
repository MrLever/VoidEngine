#pragma once
//STD Headers
#include <cstddef>
#include <functional>

//Library Headers

//Coati Headers

namespace EngineCore {

	enum class MouseButton : unsigned {
		Left = 0,
		Right = 1,
		Middle = 2,
		Thumb_1 = 3,
		Thumb_2 = 4
	};

	class MouseInput {
	private:
		//Private Class Memberss
		MouseButton Button;
		double TimeStamp;

	public:
		//tors
		MouseInput(MouseButton button);
		MouseInput(MouseButton button, double timeStamp);
		~MouseInput();

	private:
		//Private Class Members

	public:
		//Public Class Members
		MouseButton GetButton() const;
		
		std::size_t Hash() const;
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