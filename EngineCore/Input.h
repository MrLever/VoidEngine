#pragma once
//STD Headers
#include <cstddef>
#include <memory>

//Library Headers

//Coati Headers
#include "EngineUtilities.h"
#include "TimeUtils.h"

namespace core {
	enum class ButtonState : unsigned {
		RELEASED = 0,
		PRESSED = 1,
		HELD = 2,
		ANY = 4
	};

	enum class InputModifier : unsigned {
		NONE = 0x0000,
		SHIFT = 0x0001,
		CTRL = 0x0002,
		ALT = 0x0004,
		SUPER = 0x0008,
		CAPS_LOCK = 0x0010,
		NUM_LOCK = 0x0020
	};

	/**
	 * @class Input
	 * @brief The Input class represent's the engine's notion of a button input.
	 * @tparam T The underlying key enumeration being used by this Input Wrapper
	 */
	template<class T>
	class Input {
	public:
		/**
		 * Constructor
		 * @param button The button this input is reporting for
		 * @param state The state of the button being reported
		 */
		Input(T button, ButtonState state);

		/**
		 * Constructor
		 * @param button The button this input is reporting for
		 * @param state The state of the button being reported
		 * @param modifier Modifier flags applied to the input
		 */
		Input(T button, ButtonState state, unsigned modifiers);

		/**
		 * Constructor
		 * @param button The button this input is reporting for
		 * @param state The state of the button being reported
		 * @param modifier Modifier flag applied to the input
		 */
		Input(T button, ButtonState state, InputModifier modifier);

		/**
		 * Constructor
		 * @param button The button this input is reporting for
		 * @param state The state of the button being reported
		 * @param modifier Modifier flags applied to the input
		 * @param time The time stamp of the input event
		 */
		Input(T button, ButtonState state, unsigned modifiers, utils::GameTime time);

		/**
		 * Constructor
		 * @param button The button this input is reporting for
		 * @param state The state of the button being reported
		 * @param modifier Modifier applied to the input
		 * @param time The time stamp of the input event
		 */
		Input(T button, ButtonState state, InputModifier modifier, utils::GameTime time);

		/**
		 * Equality operator
		 */
		virtual bool operator==(const Input& other) const;

		/**
		 * Gets the button for this Input event
		 * @return the button
		 */
		T GetButton() const;

		/**
		 * Gets the state of the button for this input event
		 * @return The button's state
		 */
		ButtonState GetButtonState() const;

		/**
		 * Gets the time stamp for this event
		 * @return The number of milliseconds since epoch that this input event was generated
		 */
		utils::GameTime GetTimeStamp() const;

		/**
		 * Hash function to allow this class to be used as a key in Associative containers
		 * @return Hash value
		 */
		virtual std::size_t Hash() const;
		
	protected:
		/** The button that triggered this input event */
		T Button;

		/** The button's state for this input event*/
		ButtonState State;

		/** Bitfield to represent input modifiers defined by InputModifier enumeration */
		unsigned Modifiers;

		/** Time stamp of this input event */
		utils::GameTime TimeStamp;
	};

	template<class T>
	inline Input<T>::Input(T button, ButtonState state) 
		: Button(button), State(state), Modifiers(0), TimeStamp(-1) {

	}

	template <class T>
	inline Input<T>::Input(T button, ButtonState state, unsigned modifiers)
		: Button(button), State(state), Modifiers(modifiers), TimeStamp(-1) {

	}

	template<class T>
	inline Input<T>::Input(T button, ButtonState state, InputModifier modifier)
		: Button(button), State(state), Modifiers(static_cast<unsigned>(modifier)), TimeStamp(0) {

	}

	template <class T>
	inline Input<T>::Input(T button, ButtonState state, unsigned modifiers, utils::GameTime time)
		: Button(button), State(state), Modifiers(modifiers), TimeStamp(time) {
		
	}

	template<class T>
	inline Input<T>::Input(T button, ButtonState state, InputModifier modifier, utils::GameTime time)
		: Button(button), State(state), Modifiers(static_cast<unsigned>(modifier)), TimeStamp(time) {

	}

	template<class T>
	inline bool Input<T>::operator==(const Input& other) const {
		return this->Button == other.Button &&
			this->State == other.State &&
			this->Modifiers == other.Modifiers;
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
	inline utils::GameTime Input<T>::GetTimeStamp() const {
		return TimeStamp;
	}
	
	template<class T>
	inline std::size_t Input<T>::Hash() const {
		return static_cast<std::size_t>(TimeStamp);
	}
}