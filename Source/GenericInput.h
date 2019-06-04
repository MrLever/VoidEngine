#pragma once
//STD Headers
#include <cstddef>

//Library Headers

//Coati Headers
#include "EngineUtilities.h"

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
		EngineUtilities::GameTime TimeStamp;

	public:
		GenericInput(T button, ButtonState state, EngineUtilities::GameTime time);
		~GenericInput() = default;

	public:
		T GetButton() const;
		ButtonState GetButtonState() const;
		EngineUtilities::GameTime GetTimeStamp() const;

		virtual std::size_t Hash() const;
	};

	//tors
	template <class T>
	GenericInput<T>::GenericInput(
		T button, ButtonState state, EngineUtilities::GameTime time
		) : Button(button), State(state), TimeStamp(time){


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
	EngineUtilities::GameTime GenericInput<T>::GetTimeStamp() const {
		return TimeStamp;
	}

	template<class T>
	std::size_t GenericInput<T>::Hash() const {
		return static_cast<std::size_t>(GetTimeStamp());
	}

}