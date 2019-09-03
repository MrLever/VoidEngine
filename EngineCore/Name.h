#pragma once
//STD Headers
#include <compare>
#include <string>

//Library Headers

//Void Engine Headers
#include "EngineUtilities.h"

namespace EngineUtils {
	struct Name {

		///CTORS
		/**
		 * Name Constructor
		 * @param id The string from which the Name is generated.
		 */
		Name(const std::string &id) : StringID(id), ID(FNV1aHash(id)) {

		}
		
		/**
		 * Name Destructor
		 */
		~Name() = default;

		/**
		 * Equality operator, other Name
		 */
		inline bool operator== (const Name& other) const;

		/**
		 * Allows equality comparison of Name to string
		 */
		friend inline bool operator== (const Name& lhs, const std::string& rhs);
		
		/**
		 * Allows equality comparison of string to Name
		 */
		friend inline bool operator== (const std::string& lhs, const Name& rhs);

		/*
		 * Allows inequality comparison of Name to string
		 */
		friend inline bool operator!= (const Name& lhs, const std::string& rhs);

		/**
		 * Allows inequality comparison of string to Name
		 */
		friend inline bool operator!= (const std::string& lhs, const Name& rhs);

		/**
		 * Three-way comparison operator for Name objects
		 */
		inline std::strong_ordering operator<=>(const Name& other) const;

		/** The string used to generate the Name*/
		std::string StringID;

		/** The Name's Unique Hash for fast comparisons */
		unsigned long long ID;
	};
	
	inline bool Name::operator== (const Name& other) const {
		return ID == other.ID;
	}

	inline bool operator== (const Name& lhs, const std::string& rhs) {
		return lhs == Name(rhs);
	}

	inline bool operator== (const std::string& lhs, const Name& rhs) {
		return Name(lhs) == rhs;
	}

	inline bool operator!= (const Name& lhs, const std::string& rhs) {
		return !(lhs == rhs);
	}

	inline bool operator!= (const std::string& lhs, const Name& rhs) {
		return !(lhs == rhs);
	}

	inline std::strong_ordering Name::operator<=>(const Name& other) const {
		return ID <=> other.ID;
	}
}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <>
	struct hash<EngineUtils::Name> { //Class to define hash function for Keyboard Input
		//Hash functor
		std::size_t operator()(const EngineUtils::Name& t) const {
			return t.ID;
		}
	};
}