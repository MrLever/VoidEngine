//STD Headers
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <utility>

//Library Headers


//Coati Headers
#include "Keybindings.h"
#include "KeyboardInput.h"
#include "Message.h"

namespace EngineCore {

	Keybindings::Keybindings() : Serializable("Settings/EngineDefaultInput.ini") {
		Load();
	}

	Keybindings::Keybindings(std::string filePath) : Serializable(std::move(filePath)) {
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

	bool Keybindings::ApplyInputSettings(const std::vector<std::string> &tokens) {
		return false;
	}

	//Public Member Functions

	bool Keybindings::AddBinding(const KeyboardInput &input, const Action &action) {

		return false;
	}

	bool Keybindings::RemoveBinding(const KeyboardInput &key) {
		if (Bindings.erase(key) > 0) {
			//Save modification
			Save();

			return true;
		}

		return false;
	}

	bool Keybindings::ReassignBinding(const KeyboardInput &key, const Action &newAction) {
		auto binding = Bindings.find(key);

		if (binding != Bindings.end()) {
			binding->second = newAction;

			//Save modification
			Save();

			return true;
		}

		return false;
	}

	Action Keybindings::GetBinding(const KeyboardInput &input) const {
		auto binding = Bindings.find(input);

		if (binding == Bindings.end()) {
			return Action("Keybinding not found.", ActionType::Error);
		}
		
		return binding->second;
	}

	bool Keybindings::Save() const {
		return false;
	}


	bool Keybindings::Load() {
		return false;
	}

}