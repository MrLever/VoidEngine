//STD Headers

//Library Headers

//Coati Headers
#include "GamepadInput.h"
#include "EngineUtilities.h"

namespace EngineCore {

	//tors
	GamepadInput::GamepadInput(GamepadButton button, ButtonState state)
		: GenericInput<GamepadButton>(button, state, 0) {

	}
	GamepadInput::GamepadInput(GamepadButton button, ButtonState state, EngineUtilities::GameTime time) 
		: GenericInput<GamepadButton>(button, state, time) {

	}

	GamepadInput::~GamepadInput() {

	}

	std::size_t GamepadInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Button));
	}

	

	//Private Member Functions


	//Public Member Functions


}