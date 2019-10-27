#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace core {

	enum class ActionType : unsigned {
		PRESSED,
		RELEASED
	};

	/**
	 * @struct InputAction
	 * @brief Struct to deliver input action data to entities
	 */
	struct InputAction {
		utils::Name Action;
		ActionType Type;

		/**
		 * Constructor
		 * @param name The string name of the action
		 */
		InputAction(const std::string& action);

		/**
		 * Constructor
		 * @param name The string name of the action
		 * @param type The input type of the action
		 */
		InputAction(const std::string& action, ActionType type);

		/**
		 * Equality comparison overload
		 */
		bool operator==(const InputAction& other) const;
	};

}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<core::InputAction> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const core::InputAction& t) const {
			auto hashStr = t.Action.StringID;
			hashStr += std::to_string(static_cast<unsigned>(t.Type));
			return utils::FNV1aHash(hashStr.c_str());
		}

	};
}