#pragma once
//STD Headers
#include <compare>
#include <string>

//Library Headers

//Void Engine Headers
#include "EngineUtilities.h"

namespace EngineCore {
	struct UUID {

		///CTORS
		/**
		 * UUID Constructor
		 * @param id The string from which the UUID is generated.
		 */
		UUID(std::string id) : StringID(id), ID(FNV1aHash(id)) {

		}
		
		/**
		 * UUID Destructor
		 */
		~UUID() = default;

		/**
		 * Equality operator
		 */
		inline bool operator== (const UUID& other) const {
			return ID == other.ID;
		}

		/**
		 * Equality operator
		 */
		inline bool operator!= (const UUID& other) const {
			return ID != other.ID;
		}

		/**
		 * Less-than comparison operator
		 */
		inline bool operator< (const UUID& other) const {
			return ID < other.ID;
		}

		/**
		 * Greater-than comparison operator
		 */
		inline bool operator> (const UUID& other) const {
			return ID > other.ID;
		}

		/** The string used to generate the UUID*/
		std::string StringID;

		/** The UUID */
		unsigned long long ID;
	};

}