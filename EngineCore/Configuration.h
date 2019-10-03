#pragma once
//STD Headers
#include <limits>
#include <memory>
#include <string>

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Resource.h"

namespace EngineUtils {
	class Configuration : public Resource {
	public:
		/**
		 * Constructor
		 * @param configFile the resource's filepath
		 */
		Configuration(const std::string& configFile);

		/**
		 * Destructor
		 * Cleans up the LuaState to guard against memory leaks
		 */
		~Configuration();

		/**
		 * Loads a lua configuration script from main memory
		 * @return whether the load was successful. 
		 */
		bool Load() override;

		/**
		 * Loads a default lua configuration if the provided resource was inacessable
		 * @return whether the load was successful.
		 */
		bool LoadErrorResource() override;

		/**
		 * Allows the resource to be intialized after loading.
		 */
		virtual void Initialize() override;

		/**
		 * Function for retrieving values from a Lua Config file
		 * @tparam T The expected type of the attribute
		 * @param attribute The requested attribute's key
		 * @return The requested attribute
		 */
		template<typename T>
		T GetAttribute(const std::string& attribute);

	private:
		/**
		 * Helper function for returning an error value if a key is not found in a config file
		 * @return defualt error value for type T
		 */
		template<typename T>
		T ReturnErrorValue();

		/** Table mapping key -> config value */
		nlohmann::json ConfigData;
	};

	template<typename T>
	inline T Configuration::GetAttribute(const std::string& attribute) {
		auto dataIter = ConfigData.find(attribute);
		if (dataIter == ConfigData.end()) {
			return ReturnErrorValue<T>();
		}
		
		auto res = dataIter->get<T>();
		
		return res;
	}

	template<typename T>
	inline T Configuration::ReturnErrorValue(){
		if (std::numeric_limits<T>::is_specialized) {
			return std::numeric_limits<T>::max();
		}
		else {
			return T();
		}
	}
}
