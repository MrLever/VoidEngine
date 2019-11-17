#pragma once
//STD Headers

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Vector.h"
#include "Factory.h"

namespace core {
	
	class Collider {
	public:
		/**
		 * Constructor
		 */
		Collider();

		/**
		 * Allows parent component to pass in configuration data
		 */
		void SetConfigData(const nlohmann::json& data);

		/**
		 * Applies configuration settings
		 */
		virtual void Initialize() = 0;

	protected:
		/** Data used to initialize component */
		nlohmann::json ShapeData;

		/** Reference to the parent component's position */
		//math::Vector3& Position;
	};

}

