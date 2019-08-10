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
		UUID(const std::string &id) : StringID(id), ID(FNV1aHash(id)) {

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
		 * Allows equality comparison of UUID to string
		 */
		friend inline bool operator== (const UUID& lhs, const std::string& rhs);
		
		/**
		 * Allows equality comparison of string to UUID
		 */
		friend inline bool operator== (const std::string& lhs, const UUID& rhs);

		/*
		 * Allows inequality comparison of UUID to string
		 */
		friend inline bool operator!= (const UUID& lhs, const std::string& rhs);

		/**
		 * Allows inequality comparison of string to UUID
		 */
		friend inline bool operator!= (const std::string& lhs, const UUID& rhs);

		/**
		 * Three-way comparison operator for UUID objects
		 */
		inline std::strong_ordering operator<=>(const UUID& other) const;

		/** The string used to generate the UUID*/
		std::string StringID;

		/** The UUID */
		unsigned long long ID;
	};
	
	inline bool UUID::operator== (const UUID& other) const {
		return ID == other.ID;
	}

	inline bool operator== (const UUID& lhs, const std::string& rhs) {
		return lhs == UUID(rhs);
	}

	inline bool operator== (const std::string& lhs, const UUID& rhs) {
		return UUID(lhs) == rhs;
	}

	inline bool operator!= (const UUID& lhs, const std::string& rhs) {
		return !(lhs == rhs);
	}

	inline bool operator!= (const std::string& lhs, const UUID& rhs) {
		return !(lhs == rhs);
	}

	inline std::strong_ordering UUID::operator<=>(const UUID& other) const {
		return ID <=> other.ID;
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