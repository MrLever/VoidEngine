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
	GamepadInput::GamepadInput(GamepadButton button, ButtonState state, EngineUtilities::GameTime time) 
		: GenericInput(static_cast<unsigned>(button), state, time) {

	}

	GamepadInput::~GamepadInput() {

	}

	bool GamepadInput::operator==(const GamepadInput& other) const {
		return (this->GetButton() == other.GetButton() && this->GetButtonState() == other.GetButtonState());
	}

	GamepadButton GamepadInput::GetGamepadButton() const {
		return static_cast<GamepadButton>(Button);
	}

	std::size_t GamepadInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Button));
	}

	

	//Private Member Functions


	//Public Member Functions


}