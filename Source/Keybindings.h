#pragma once
//STD Headers
#include <unordered_map>
#include <string>

//Library Headers

//Coati Headers
#include "KeyboardInput.h"
#include "Serializable.h"

namespace EngineCore {

	//Forward Class declarations
	class Message;

	class Keybindings : Serializable {
	private:
		//Private Class Members
		std::unordered_map<KeyboardInput, Message> Bindings;

	public:
		//CTORS
		Keybindings();
		Keybindings(std::string filePath);
		~Keybindings();

	private:
		//Private Member Functions
		std::vector<std::string> LoadInputSettings();
		bool ApplyInputSettings(std::vector<std::string> tokens);

	public:
		//Public Member Functions
		bool AddBinding(KeyboardInput input, std::string event, int eventType);
		bool AddBinding(KeyboardInput input, Message event);
		bool RemoveBinding(KeyboardInput key);
		bool ReassignBinding(KeyboardInput key, std::string event, int EventType);
		bool ReassignBinding(KeyboardInput key, Message newEvent);

		Message GetBinding(KeyboardInput input) const;

		virtual bool Save() const override;
		virtual bool Load() override;
	};

}