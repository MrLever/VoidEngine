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

Keybindings::Keybindings(std::string filePath) : Serializable(filePath) {
	Load();
}

Keybindings::~Keybindings() {
	Save();
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

	inFileStream.close();

	return tokens;
}

bool Keybindings::ApplyInputSettings(std::vector<std::string> tokens) {
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

bool Keybindings::AddBinding(KeyboardInput input, std::string event, int eventType) {
	Message bindingEvent(event, eventType);
	Bindings.insert({input, bindingEvent});

	return true;
}

bool Keybindings::AddBinding(KeyboardInput input, Message event) {
	Bindings.insert({ input, event });

	return true;
}

bool Keybindings::RemoveBinding(KeyboardInput key) {
	if (Bindings.erase(key) > 0) {
		//Save modification
		Save();

		return true;
	}

	return false;	
}

bool Keybindings::ReassignBinding(KeyboardInput key, std::string event, int EventType) {
	auto binding = Bindings.find(key);

	if (binding != Bindings.end()) {
		Message newEvent = Message(event, EventType);
		binding->second = newEvent;

		//Save modification
		Save();

		return true;
	}

	return false;
}

bool Keybindings::ReassignBinding(KeyboardInput key, Message newEvent) {
	auto binding = Bindings.find(key);

	if (binding != Bindings.end()) {
		binding->second = newEvent;

		//Save modification
		Save();

		return true;
	}

	return false;
}

Message Keybindings::GetBinding(KeyboardInput input) {
	auto binding = Bindings.find(input);

	if (binding == Bindings.end()) {
		return Message("Keybinding not found.", MessageType::Error);
	}
	else {
		return binding->second;
	}	
}

bool Keybindings::Save() {
	std::ofstream OutFileStream;
	OutFileStream.open(FilePath);
	if (!OutFileStream) {
		std::cerr << "ERROR: Keybindings file not found\n";
		return false;
	}

	for (auto binding : Bindings) {
		OutFileStream << static_cast<int>(binding.first.GetKey()) << ",";
		OutFileStream << binding.second.GetEvent() << ",";
		OutFileStream << static_cast<unsigned>(binding.second.GetType()) << ",\n";
	}
	OutFileStream << -1;

	OutFileStream.close();
	return true;
}


bool Keybindings::Load() {
	//Clear any previous bindings
	Bindings.clear();

	//Load new bindings
	return ApplyInputSettings(LoadInputSettings());

}
