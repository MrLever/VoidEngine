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

namespace EngineCore {

	Keybindings::Keybindings() : Serializable("Settings/EngineDefaultInput.ini") {
		Load();
	}

	Keybindings::Keybindings(std::string filePath) : Serializable(filePath) {
		Load();
	}

	Keybindings::~Keybindings() {
		//Save();
	}


	//Private Member Functions
	std::vector<std::string> Keybindings::LoadInputSettings() {
		std::ifstream inFileStream;
		std::vector<std::string> tokens;

		inFileStream.open(FilePath);

		inFileStream.close();

		return tokens;
	}

	bool Keybindings::ApplyInputSettings(std::vector<std::string> tokens) {
		return false;
	}

	//Public Member Functions

	bool Keybindings::AddBinding(KeyboardInput input, std::string event, int eventType) {
		Message bindingEvent(event, eventType);
		Bindings.insert({ input, bindingEvent });

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

	Message Keybindings::GetBinding(KeyboardInput input) const {
		auto binding = Bindings.find(input);

		if (binding == Bindings.end()) {
			return Message("Keybinding not found.", MessageType::Error);
		}
		
		return binding->second;
	}

	bool Keybindings::Save() const {
		std::ofstream OutFileStream;
		OutFileStream.open(CustomInputPath);
		if (!OutFileStream) {
			std::cerr << "ERROR: Keybindings file not found\n";
			return false;
		}

		OutFileStream << "[INPUT EVENTS]\n";

		OutFileStream.close();
		return true;
	}


	bool Keybindings::Load() {
		//Clear any previous bindings
		Bindings.clear();

		//Load new bindings
		return ApplyInputSettings(LoadInputSettings());

	}

}