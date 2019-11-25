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

		/**
		 * Returns dynamic type
		 */
		virtual utils::Name GetTypename() const = 0;

		/**
		 * Returns name of static Collider Type
		 */
		static utils::Name GetStaticTypename();

	protected:
		/** Data used to initialize component */
		nlohmann::json ShapeData;
		
		static const float COLLISION_EPSILON;
	};

}

