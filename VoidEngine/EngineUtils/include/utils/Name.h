#pragma once
//STD Headers
#include <compare>
#include <string>
#include <unordered_map>
#include <ostream>

//Library Headers

//Void Engine Headers
#include "utils/EngineUtilities.h"

namespace utils {
	/**
	 * @class Name
	 * @brief Name is a class used to enable fast string comparisons through use of hashing
	 */
	struct Name {
		/**
		 * Name Constructor
		 */
		Name();

		/**
		 * Conversion constructor, char*
		 */
		Name(const char* id);

		/**
		 * Conversion construtor, std::string
		 * @param id The string from which the Name is generated.
		 */
		Name(const std::string& id);
		
		/**
		 * Name Destructor
		 */
		~Name() = default;

		/**
		 * Assignment operator, other name
		 * @param other the name to assign to this instance
		 */
		Name& operator= (const Name& other);

		/** Equality comparison operator */
		inline bool operator== (const Name& other) const;

		/** Inequality comparison operator */
		inline bool operator!= (const Name& other) const;

		/**
		 * Output stream operator overload
		 */
		friend inline std::ostream& operator<< (std::ostream& out, const Name& other);

		/**
		 * Three-way comparison operator for Name objects
		 */
		inline std::strong_ordering operator<=>(const Name& other) const;

		/** The string used to generate the Name*/
		std::string StringID;

		/** The Name's Unique Hash for fast comparisons */
		uint32_t ID;

	};

	inline Name::Name() : StringID(""), ID(FNV1aHash("")){

	}

	inline Name::Name(const char* id) : StringID(id), ID(FNV1aHash(id)) {

	}

	inline Name::Name(const std::string& id) : StringID(id), ID(FNV1aHash(id.c_str())) {

	}

	inline Name& Name::operator=(const Name& other) {
		if (other == *this) {
			return *this;
		}

		ID = other.ID;
		StringID = other.StringID;
		return *this;
	}

	inline bool Name::operator== (const Name& other) const {
		return ID == other.ID;
	}

	inline bool Name::operator!= (const Name& other) const {
		return !(*this == other);
	}

	inline std::ostream& operator<< (std::ostream& out, const Name& name) {
		out << name.StringID;
		return out;
	}

	inline std::strong_ordering Name::operator<=>(const Name& other) const {
		return ID <=> other.ID;
	}
}

//It is acceptable to extend the std namespace to add template specifications for 
//standard library templates to work with custom data types.
namespace std {
	template <>
	struct hash<utils::Name> { //Class to define hash function for Keyboard Input
		//Hash functor
		std::size_t operator()(const utils::Name& t) const {
			return t.ID;
		}
	};
}