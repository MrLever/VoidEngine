#pragma once
//STD Headers
#include <cstddef>
#include <memory>

//Library Headers

//Coati Headers
#include "EngineUtilities.h"
#include "TimeUtils.h"

namespace EngineCore {
	enum class ButtonState : unsigned {
		Released = 0,
		Pressed = 1,
		Held = 2,
		Any = 4
	};

	template<class T>
	class Input {

	public:
		Input(T button, ButtonState state);
		Input(T button, ButtonState state, EngineUtils::GameTime time);
		~Input() = default;

		virtual bool operator==(const Input& other) const;

		T GetButton() const;
		ButtonState GetButtonState() const;
		EngineUtils::GameTime GetTimeStamp() const;

		virtual std::size_t Hash() const;
		
	protected:
		T Button;
		ButtonState State;
		EngineUtils::GameTime TimeStamp;
	};

	template <class T>
	inline Input<T>::Input(T button, ButtonState state)
		: Button(button), State(state), TimeStamp(-1) {

	}

	template <class T>
	inline Input<T>::Input(T button, ButtonState state, EngineUtils::GameTime time)
		: Button(button), State(state), TimeStamp(time) {
		
	}

	template<class T>
	inline bool Input<T>::operator==(const Input& other) const {
		return this->Button == other.Button &&
			this->State == other.State;
	}

	template<class T>
	inline T Input<T>::GetButton() const {
		return Button;
	}

	template<class T>
	inline ButtonState Input<T>::GetButtonState() const {
		return State;
	}
	
	template<class T>
	inline EngineUtils::GameTime Input<T>::GetTimeStamp() const {
		return TimeStamp;
	}
	
	template<class T>
	inline std::size_t Input<T>::Hash() const {
		return static_cast<std::size_t>(TimeStamp);
	}
}