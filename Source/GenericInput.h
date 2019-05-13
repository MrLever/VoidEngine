#pragma once
//STD Headers
#include <cstddef>

//Library Headers

//Coati Headers

namespace EngineCore {
	enum class ButtonState : unsigned {
		Released = 0,
		Pressed = 1,
		Held = 2,
		Any = 4
	};

	template <class T>
	class GenericInput {

	protected:
		T Button;
		ButtonState State;
		double TimeStamp;

	public:
		GenericInput(T button, ButtonState state, double time);
		~GenericInput();

	public:
		T GetButton() const;
		ButtonState GetButtonState() const;
		double GetTimeStamp() const;

		virtual std::size_t Hash() const = 0;
	};

	//tors
	template <class T>
	GenericInput<T>::GenericInput(T button, ButtonState state, double time) 
		: Button(button), State(state), TimeStamp(time){

	}

	template <class T>
	GenericInput<T>::~GenericInput() {
	
	}

	template <class T>
	T GenericInput<T>::GetButton() const {
		return Button;
	}

	template <class T>
	ButtonState GenericInput<T>::GetButtonState() const {
		return State;
	}

	template <class T>
	double GenericInput<T>::GetTimeStamp() const {
		return TimeStamp;
	}

}