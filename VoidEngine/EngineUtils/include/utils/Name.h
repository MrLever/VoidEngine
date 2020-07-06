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
		 * Name Constructor
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

		/**
		 * Assignment operator, string
		 * @param name, the name to assign to this instance
		 */
		Name& operator= (const std::string& name);

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

	inline Name& Name::operator=(const std::string& name) {
		if (StringID == name) {
			return *this;
		}

		StringID = name;
		ID = FNV1aHash(name.c_str());
		return *this;
	}

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