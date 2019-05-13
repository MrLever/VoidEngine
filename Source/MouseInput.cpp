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

	MouseInput::MouseInput(MouseButton button, ButtonState state, double timeStamp) 
		: GenericInput<MouseButton>(button, state, 0) {
	
	}


	MouseInput::~MouseInput() {

	}

	//Private Member Functions

	//Public Memeber Functions

	std::size_t MouseInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Button));
	}
}