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
	struct Type {
		/** Name of the type as a hashed string */
		utils::Name m_Name;

		/** Size of the type in bytes */
		size_t m_Size;
	};

	/**
	 * @struct Field
	 * @brief Description of a reflected class member 
	 */
	struct Field {
		/** The type of the class member */
		Type* m_Type;

		/** The name of the class memeber */
		utils::Name m_Name;

		/** The offset of the class member in memory */
		size_t offset;
	};

	struct Function {
		Type m_ReturnValue;

	};

	struct Class : public Type {
		
	};

}