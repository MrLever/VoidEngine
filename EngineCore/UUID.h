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
		inline bool operator== (const UUID& other) const;

		/**
		 * Three-way comparison operator for UUID objects
		 */
		inline std::strong_ordering operator<=>(const UUID& other) const;

		/**
		 * The next two function overloads allow for implicit equality comparisions
		 * between strings and UUIDs
		 */
		friend inline bool operator== (const UUID& lhs, const std::string& rhs);
		friend inline bool operator== (const std::string& lhs, const UUID& rhs);

		/** The string used to generate the UUID*/
		std::string StringID;

		/** The UUID */
		unsigned long long ID;
	};
	
	inline bool UUID::operator== (const UUID& other) const {
		return ID == other.ID;
	}

	inline std::strong_ordering UUID::operator<=>(const UUID& other) const {
		return ID <=> other.ID;
	}

	inline bool operator== (const UUID& lhs, const std::string& rhs) {
		return lhs == UUID(rhs);
	}

	inline bool operator== (const std::string& lhs, const UUID& rhs) {
		return UUID(lhs) == rhs;
	}
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