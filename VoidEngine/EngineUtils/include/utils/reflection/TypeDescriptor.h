#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Name.h"

namespace utils::reflection {
	
}

namespace utils {
	//Forward declare typedescriptor for forward declaration of GetType
	struct TypeDescriptor;

	namespace reflection {
		//forward declare GetType
		inline const TypeDescriptor& GetType(const utils::Name& name);
	}

	/**
	 * @struct Type
	 * @brief The base description of a type in the reflection system
	 */
	struct TypeDescriptor {

		friend inline const TypeDescriptor& reflection::GetType(const utils::Name& name);

		TypeDescriptor(const utils::Name& name, size_t size);

		/** Name of the type as a hashed string */
		const utils::Name m_Name;

		/** Size of the type in bytes */
		const size_t m_Size;

		bool operator== (const TypeDescriptor& other) const;

	private:
		static std::unordered_map<utils::Name, TypeDescriptor&> s_TypeRegistry;
	};
}