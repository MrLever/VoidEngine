#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Name.h"

namespace core {

	struct AxisInputAction {
		utils::Name AxisName;
		float Value;

		/**
		 * Constructor
		 * @param name The axis' name
		 * @param value The axis' reading
		 */
		AxisInputAction(const utils::Name& name, float value);

		/**
		 * Constructor
		 * @param name The axis' name
		 * @param value The axis' reading
		 */
		AxisInputAction(const std::string& name, float value);

		/**
		 * Equality comparison overload
		 */
		bool operator==(const AxisInputAction& other) const;
	};

}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <> struct hash<core::AxisInputAction> { //Class to define hash function for Keyboard Input

		//Hash functor
		std::size_t operator()(const core::AxisInputAction& t) const {
			auto hashStr = t.AxisName.StringID;
			return utils::FNV1aHash(hashStr.c_str());
		}

	};
}