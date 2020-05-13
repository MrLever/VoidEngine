#pragma once
//STD Headers

//Library headers
#include <nlohmann/json.hpp>

//Void Engine Headers
#include "Entity.h"

namespace core {

	/**
	 * Prototypes store all the data needed to spawn copies of an entity from a configuration.
	 */
	class Prototype final {
	public:
		
		/**
		 * Trivial constructor
		 */
		Prototype() = default;

		/**
		 * Constructor
		 * @param data The data to use when creating an instance of the Prototype
		 */
		Prototype(const nlohmann::json& data);

		/**
		 * Destructor
		 */
		~Prototype() = default;

		/**
		 * Accessor for Prototype data, used in entity construction
		 */
		const nlohmann::json& GetData() const;

	private:
		nlohmann::json m_Data;

	};

}