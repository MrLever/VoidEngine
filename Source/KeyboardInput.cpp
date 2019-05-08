//STD Headers
#include <limits>
#include <functional>

//Library Headers


//Coati Headers
#include "KeyboardInput.h"

namespace EngineCore {

	//tors
	KeyboardInput::KeyboardInput(KeyType key, KeyState state) {
		this->Key = key;
		this->State = state;
		this->TimeStamp = -std::numeric_limits<double>::infinity();
	}

	KeyboardInput::KeyboardInput(KeyType key, KeyState state, double time) {
		this->Key = key;
		this->State = state;
		this->TimeStamp = time;
	}

	KeyboardInput::~KeyboardInput() {

	}


	bool KeyboardInput::operator==(const KeyboardInput& other) const {
		return (this->GetKey() == other.GetKey() && this->GetKeyState() == other.GetKeyState());
	}




	//Private Member Functions


	//Public Member Functions

	KeyType KeyboardInput::GetKey() const {
		return Key;
	}

	KeyState KeyboardInput::GetKeyState() const {
		return State;
	}

	// Keyboard input objects are hashed by feeding their key value
	// to the standard library's hash function for ints.
	std::size_t KeyboardInput::Hash() const {
		return std::hash<int>()(static_cast<int>(Key));
	}

}