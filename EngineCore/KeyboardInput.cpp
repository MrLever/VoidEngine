//STD Headers
#include <limits>
#include <functional>

//Library Headers


//Coati Headers
#include "KeyboardInput.h"

namespace EngineCore {

	//tors
	KeyboardInput::KeyboardInput(KeyboardButton key, ButtonState state) 
		: GenericInput(static_cast<unsigned>(key), state, 0) {

	}

	KeyboardInput::KeyboardInput(KeyboardButton key, ButtonState state, EngineUtilities::GameTime time)
		: GenericInput(static_cast<unsigned>(key), state, time){

	}

	KeyboardInput::~KeyboardInput() {

	}

	std::size_t KeyboardInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Button));
	}


	//Private Member Functions


	//Public Member Functions


}