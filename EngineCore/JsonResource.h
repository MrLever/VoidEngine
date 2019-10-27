#pragma once
//STD Headers

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Resource.h"

namespace utils {

	/**
	 * @class JsonResource
	 * @brief There are several resource types that rely on the JSON data format.
	 *        This class provides common functionalities to all of them.
	 */
	class JsonResource : public Resource {
	public:
		/**
		 * Constructor
		 * @param filePath the location of the resource in main memory
		 */
		JsonResource(const std::string& filePath);

		/**
		 * Loads json data from main memory
		 */
		virtual bool Load() override;

		/**
		 * Loads the resource's default value if the path provided is invalid
		 */
		virtual bool LoadErrorResource() override;

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
		T GetAttribute(const std::string& attribute) const;

	private:
		/**
		 * Helper function for returning an error value if a key is not found in a json file
		 * @return defualt error value for type T
		 */
		template<typename T>
		T ReturnErrorValue() const;

		/** A queryable JSON object that can be accessed through GetAttribute() */
		nlohmann::json Data;

	};

	template<typename T>
	inline T JsonResource::GetAttribute(const std::string& attribute) const {
		auto dataIter = Data.find(attribute);
		if (dataIter == Data.end()) {
			std::stringstream warning;
			warning << "Key [" << attribute << "] not found in JSON resource [" << ResourcePath << "]";

			utils::Logger::LogWarning(warning.str());
			return ReturnErrorValue<T>();
		}

		auto res = dataIter->get<T>();

		return res;
	}

	template<typename T>
	inline T JsonResource::ReturnErrorValue() const {
		std::stringstream warning;
		warning << "Generating defualted error value for type " << typeid(T).name();
		utils::Logger::LogWarning(warning.str());

		if (std::numeric_limits<T>::is_specialized) {
			return std::numeric_limits<T>::max();
		}
		else {
			return T();
		}
	}

}
