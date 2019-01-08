//STD Headers
#include <typeindex> 

//Library Headers


//Coati Headers
#include "KeyboardInput.h"



KeyboardInput::KeyboardInput(KeyType Key, KeyState State) {
	this->Key = Key;
	this->State = State;
}


KeyboardInput::~KeyboardInput() {
}

bool KeyboardInput::operator==(const KeyboardInput &other) const{
	return (
		this->GetKey() == other.GetKey() 
		&& this->GetKeyState() == other.GetKeyState()
	);
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