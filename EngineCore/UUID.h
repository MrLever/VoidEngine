#pragma once
//STD Headers
#include <compare>
#include <string>

//Library Headers

//Void Engine Headers
#include "EngineUtilities.h"

namespace EngineUtils {
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
		 * Equality operator, other UUID
		 */
		inline bool operator== (const UUID& other) const {
			return ID == other.ID;
		}

		/**
		 * Equality operator, UUID and string
		 */
		inline bool operator== (const std::string& other) const {
			return ID == FNV1aHash(other);
		}

		/**
		 * Inequality operator
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

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <>
	struct hash<EngineUtils::UUID> { //Class to define hash function for Keyboard Input
		//Hash functor
		std::size_t operator()(const EngineUtils::UUID& t) const {
			return t.ID;
		}
	};
}