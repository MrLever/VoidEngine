#pragma once
//STD Headers
#include <unordered_map>
#include <string>

//Library Headers

//Coati Headers
#include "KeyboardInput.h"
#include "Serializable.h"
#include "Action.h"

namespace EngineCore {

	class Keybindings : Serializable {
	private:
		//Private Class Members
		std::unordered_map<KeyboardInput, Action> Bindings;
		const std::string CustomInputPath = "Settings/UserCustomInput.ini";

	public:
		//CTORS
		Keybindings();
		Keybindings(std::string filePath);
		~Keybindings();

	private:
		//Private Member Functions
		std::vector<std::string> LoadInputSettings();
		bool ApplyInputSettings(const std::vector<std::string> &tokens);

	public:
		//Public Member Functions
		bool AddBinding(const KeyboardInput &input, const Action &action);
		bool RemoveBinding(const KeyboardInput &key);
		bool ReassignBinding(const KeyboardInput &key, const Action &newACtion);

		Action GetBinding(const KeyboardInput &input) const;

		bool Save() const override;
		bool Load() override;
	};

}