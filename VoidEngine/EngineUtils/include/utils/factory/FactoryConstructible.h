#pragma once
//STD Headers

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "utils/Name.h"

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
		virtual void SetConfigData(const nlohmann::json& data) { configData = data; }

	protected:
		/**
		 * @return Does configdata contain the key we are searching for
		 */
		inline bool DataContainsKey(const std::string& key) { return configData.find(key) != configData.end(); }

		/** Data used to initialize component */
		nlohmann::json configData;
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