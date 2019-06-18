#pragma once
//STD Headers
#include <unordered_map>
#include <string>

//Library Headers

//Coati Headers
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamepadInput.h"
#include "Serializable.h"
#include "Action.h"

namespace EngineCore {

	class Keybindings : Serializable {
	private:
		//Private Class Members
		std::unordered_map<KeyboardInput, Action> KeyboardBindings;
		std::unordered_map<MouseInput, Action> MouseBindings;
		std::unordered_map<GamepadInput, GamepadInput> GamepadBindings;

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
		bool AddBinding(const MouseInput &input, const Action &action);
		bool AddBinding(const GamepadInput &input, const Action &action);

		bool RemoveBinding(const KeyboardInput &key);
		bool RemoveBinding(const MouseInput &key);
		bool RemoveBinding(const GamepadInput &key);

		bool ReassignBinding(const KeyboardInput &key, const Action &newAction);

		Action GetBinding(const KeyboardInput &input) const;

		bool Save() const override;
		bool Load() override;
	};

}