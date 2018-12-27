//STD Headers


//Library Headers


//Coati Headers
#include "KeyboardInput.h"



KeyboardInput::KeyboardInput(KeyType Key, KeyState State) {
	this->Key = Key;
	this->State = State;
}


KeyboardInput::~KeyboardInput() {
}


//Private Member Functions


//Public Member Functions

KeyType KeyboardInput::GetKey() {
	return Key;
}

KeyState KeyboardInput::GetKeyState() {
	return State;
}
