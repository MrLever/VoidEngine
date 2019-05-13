//STD Headers
#include <limits>
#include <functional>

//Library Headers


//Coati Headers
#include "KeyboardInput.h"

namespace EngineCore {

	//tors
	KeyboardInput::KeyboardInput(KeyType key, ButtonState state) : GenericInput<KeyType>(key, state, 0) {

	}

	KeyboardInput::KeyboardInput(KeyType key, ButtonState state, double time) 
		: GenericInput<KeyType>(key, state, time){

	}

	KeyboardInput::~KeyboardInput() {

	}


	bool KeyboardInput::operator==(const KeyboardInput& other) const {
		return (this->GetButton() == other.GetButton() && this->GetButtonState() == other.GetButtonState());
	}


	//Private Member Functions


	//Public Member Functions


	// Keyboard input objects are hashed by feeding their key value
	// to the standard library's hash function for ints.
	std::size_t KeyboardInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Button));
	}

}