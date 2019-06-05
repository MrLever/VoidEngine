//STD Headers

//Library Headers


//Coati Headers
#include "GenericInput.h"

namespace EngineCore {
	//tors

	GenericInput::GenericInput( unsigned button, ButtonState state, EngineUtilities::GameTime time) 
		: Button(button), State(state), TimeStamp(time) {


	}

	unsigned GenericInput::GetButton() const {
		return Button;
	}

	ButtonState GenericInput::GetButtonState() const {
		return State;
	}

	EngineUtilities::GameTime GenericInput::GetTimeStamp() const {
		return TimeStamp;
	}

	std::size_t GenericInput::Hash() const {
		return static_cast<std::size_t>(GetTimeStamp());
	}

}