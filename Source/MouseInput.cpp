//STD headers
#include <functional>

//Library headers

//Coati Headers
#include "MouseInput.h"


namespace EngineCore {
	
	//tors
	MouseInput::MouseInput(MouseButton button, ButtonState state) 
		: GenericInput<MouseButton>(button, state, 0) {

	}

	MouseInput::MouseInput(MouseButton button, ButtonState state, EngineUtilities::GameTime timeStamp) 
		: GenericInput<MouseButton>(button, state, timeStamp) {
	
	}


	MouseInput::~MouseInput() {

	}

	bool MouseInput::operator==(const MouseInput& other) const {
		return (this->GetButton() == other.GetButton() && this->GetButtonState() == other.GetButtonState());
	}

	std::size_t MouseInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Button));
	}

	//Private Member Functions

	//Public Memeber Functions

}