//STD Headers
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

//Library Headers


//Coati Headers
#include "Keybindings.h"
#include "KeyboardInput.h"
#include "Message.h"


Keybindings::Keybindings() : Serializable("Settings/input.ini") {
	Load();
}


Keybindings::~Keybindings() {
}


//Private Member Functions
std::vector<std::string> Keybindings::LoadInputSettings() {
	std::ifstream inFileStream;
	std::vector<std::string> tokens;

	inFileStream.open(FilePath);
	
	if (!inFileStream.is_open()) {
		//Return empty token array on error
		return std::vector<std::string>();
	}

	for (std::string token; std::getline(inFileStream, token, ','); ) {
		tokens.push_back(token);
	}

	return tokens;
}

bool Keybindings::ProcessInputSettings(std::vector<std::string> tokens) {
	if (tokens.size() < 1) {
		return false;
	}
	
	for (auto i = 0; i < tokens.size(); i+= 3) {
		int keyToken = std::stoi(tokens[i]);
		
		if (keyToken == -1) {
			break;
		}
		
		std::string inputEvent = tokens[i + 1];
		int messageType = std::stoi(tokens[i + 2]);

		KeyboardInput key(static_cast<KeyType>(keyToken), KeyState::Pressed);
		AddBinding(key, inputEvent, messageType);

	}

	return true;
}

//Public Member Functions

void Keybindings::AddBinding(KeyboardInput input, std::string event, int eventType) {
	Message bindingEvent(event, eventType);
	Bindings.insert({input, bindingEvent});
}

void Keybindings::RemoveBinding(KeyboardInput key) {
	//Do stuff

	//Save it
	Save();
}

void Keybindings::ReassignBinding(KeyboardInput key, std::string event, int EventType) {
	//Do something

	//Save it
	Save();
}

Message Keybindings::GetBinding(KeyboardInput input) {
	auto binding = Bindings.find(input);

	if (binding == Bindings.end()) {
		return Message("Keybinding not found.", Error);
	}
	else {
		return binding->second;
	}	
}

bool Keybindings::Save() {
	return true;
}


bool Keybindings::Load() {
	//Clear any previous bindings
	Bindings.clear();

	//Load new bindings
	return ProcessInputSettings(LoadInputSettings());

}
