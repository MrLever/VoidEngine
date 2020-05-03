#pragma once
//STD Headers
#include <concepts>

//Library Headers

//Void Engine Headers
#include "core/VEObject.h"

namespace core {
	
	enum class EventCategory : unsigned char {
		NONE = 0x00,
		RAW_INPUT = 0x01,
		INPUT = 0x02,
		WINDOW = 0x04,
		GAMEPLAY = 0x08
	};

	using EventID = uint32_t;

	class Event : public VEObject {
		
		TYPE_INFO_DECL(Event);
		
	public:
		/**
		 * Constructor
		 */
		Event();

		/** Boolean to determine if an event has been processed */
		bool eventHandled;
	};

}
