//STD headers
#include <functional>

//Library headers

//Coati Headers
#include "MouseInput.h"


namespace EngineCore {
	
	//tors
	MouseInput::MouseInput(MouseButton button, ButtonState state) 
		: GenericInput(static_cast<unsigned>(button), state, 0) {

	}

	MouseInput::MouseInput(MouseButton button, ButtonState state, EngineUtilities::GameTime timeStamp) 
		: GenericInput(static_cast<unsigned>(button), state, timeStamp) {
	
	}


	MouseInput::~MouseInput() {

	}

	std::size_t MouseInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Button));
	}

	//Private Member Functions

	//Public Memeber Functions

}