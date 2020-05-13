#pragma once
//STD Headers
#include <concepts>

//Library Headers

//Void Engine Headers
#include "core/VEObject.h"

namespace core {
	
	using EventID = uint32_t;

	class Event : public VEObject {
		
		ENABLE_RTTI(Event);
		
	public:
		/**
		 * Constructor
		 */
		Event();

		/** Boolean to determine if an event has been processed */
		bool eventConsumed;
	};

}
