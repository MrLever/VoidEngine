//STD Headers

//Library Headers

//Coati Headers
#include "GamepadInput.h"
#include "EngineUtilities.h"

namespace EngineCore {

	//tors
	GamepadInput::GamepadInput(GamepadButton button, ButtonState state)
		: GenericInput(static_cast<unsigned>(button), state, 0) {

	}
	GamepadInput::GamepadInput(GamepadButton button, ButtonState state, EngineUtils::GameTime time) 
		: GenericInput(static_cast<unsigned>(button), state, time) {

	}

	GamepadInput::~GamepadInput() {

	}

	std::size_t GamepadInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Button));
	}

	

	//Private Member Functions


	//Public Member Functions


}