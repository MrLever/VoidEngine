//STD headers
#include <functional>

//Library headers

//Coati Headers
#include "MouseInput.h"

namespace EngineCore {
	
	//tors
	MouseInput::MouseInput(MouseButton button) : Button(button), TimeStamp(0) {

	}

	MouseInput::MouseInput(MouseButton button, double timeStamp) : Button(button), TimeStamp(timeStamp) {
	
	}


	MouseInput::~MouseInput() {

	}

	//Private Member Functions

	//Public Memeber Functions

	MouseButton MouseInput::GetButton() const {
		return Button;
	}

	std::size_t MouseInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Button));
	}
}