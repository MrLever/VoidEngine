#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Name.h"

namespace utils {
	/**
	 * @struct Type
	 * @brief The base description of a type in the reflection system
	 */
	struct TypeDescriptor {
		/** Name of the type as a hashed string */
		utils::Name m_Name;

		/** Size of the type in bytes */
		size_t m_Size;

		bool operator== (const TypeDescriptor& other) const;
	};
}