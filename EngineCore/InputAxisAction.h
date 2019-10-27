#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace core {

	struct InputAxisAction {
		utils::Name AxisName;
		float Value;

		/**
		 * Constructor
		 * @param name The axis' name
		 * @param value The axis' reading
		 */
		InputAxisAction(const utils::Name& name, float value);

		/**
		 * Constructor
		 * @param name The axis' name
		 * @param value The axis' reading
		 */
		InputAxisAction(const std::string& name, float value);

		/**
		 * Equality comparison overload
		 */
		bool operator==(const InputAxisAction& other) const;
	};

}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<core::InputAxisAction> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const core::InputAxisAction& t) const {
			auto hashStr = t.AxisName.StringID;
			return utils::FNV1aHash(hashStr.c_str());
		}

	};
}