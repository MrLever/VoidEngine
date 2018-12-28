//STD Headers
#include <unordered_map>
#include <string>

//Library Headers


//Coati Headers
#include "Keybindings.h"
#include "Message.h"


Keybindings::Keybindings() : Serializable("Settings/input.ini") {
}


Keybindings::~Keybindings() {
}

//Private Member Functions

//Public Member Functions

void Keybindings::AddBinding(KeyboardInput input, std::string event, int eventType) {
	Message bindingEvent(event, eventType);
}

Message Keybindings::GetBinding(KeyboardInput input) {

	return Message("Keybinding not found.", Error);
	//return (it != Bindings.end()) ?
	//	Message("Keybinding not found.", Error) :
	//	it->second;
}

void Keybindings::Save() {
}

void Keybindings::Load() {
}
