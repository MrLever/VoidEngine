#pragma once
//STD Headers

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Name.h"

namespace utils {

	/**
	 * @class FactoryConstructible
	 * @brief Provides derived class with interface for being factory constructible.
	 * @note Expects all subclasses to write a GetStaticTypename()
	 */
	class FactoryConstructible {
	public:
		/**
		 * Constructor
		 */
		FactoryConstructible() {};

		/**
		 * Returns dynamic type
		 */
		virtual utils::Name GetTypename() const = 0;

		/**
		 * Returns name of static object type
		 */
		static utils::Name GetStaticTypename() { return utils::Name("Unspecialized Factory Object"); }

		/**
		 * Allows factory to attatch configuration data to object
		 */
		virtual void SetConfigData(const nlohmann::json& data) { ConfigData = data; }

	protected:
		/** Data used to initialize component */
		nlohmann::json ConfigData;
	};

}

//Shorthand macros to make specifying type info less error prone
#define TYPE_INFO_DECL(CLAZZ) \
public:\
virtual utils::Name GetTypename() const override; \
static utils::Name GetStaticTypename();

#define TYPE_INFO_IMPL(CLAZZ) \
utils::Name CLAZZ::GetTypename() const { return utils::Name(#CLAZZ); } \
utils::Name CLAZZ::GetStaticTypename() { return utils::Name(#CLAZZ); } 