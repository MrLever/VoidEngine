#pragma once
//STD Headers

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

	typedef uint32_t EventID;

	class Event : public VEObject {
		
		TYPE_INFO_DECL(Event);
		
	public:
		/**
		 * Constructor
		 */
		Event();
		
		virtual EventCategory GetEventCategory() const = 0;

		EventID GetID() const;

		/** Boolean to determine if an event has been processed */
		bool eventHandled;
	};

}
