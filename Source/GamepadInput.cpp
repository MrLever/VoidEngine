//STD Headers

//Library Headers

//Coati Headers
#include "GamepadInput.h"

namespace EngineCore {

	//tors
	GamepadInput::GamepadInput(GamepadButton button, ButtonState state)
		: GenericInput<GamepadButton>(button, state, 0) {

	}
	GamepadInput::GamepadInput(GamepadButton button, ButtonState state, double time) 
		: GenericInput<GamepadButton>(button, state, time) {

	}

	GamepadInput::~GamepadInput() {

	}

	

	//Private Member Functions


	//Public Member Functions
	std::size_t GamepadInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Button));
	}

}