#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Name.h"

namespace utils {
	struct Type;

	/**
	 * @struct Propery
	 * @brief A named member of a derived or user defined type
	 */
	struct Property {
		//Allow Class Type Descriptors to set and get properties
		friend struct utils::Class;

		/** The type of the class member */
		const Type& m_Type;

		/** The name of the class memeber */
		utils::Name m_Name;

		/** The offset of the class member in memory */
		size_t m_Offset;

	private:
		/**
		 * Allows user to modify instance of a property through it's reflection data
		 * @param instance The pointer to the class instance that holds this property
		 */
		template<class T>
		void Set(void* instance, const T& value);

		/**
		 * Allows user to access a property through it's reflection data
		 * @param instance The pointer to the class instance that holds this property
		 */
		template<class T>
		std::optional<T> Get(const void* instance) const;

	};

	template<class T>
	inline void Property::Set(void* instance, const T& value) {
		//Require type match to modify memory
		assert(&m_Type == &GetType<T>());

		std::memcpy(
			((char*)instance) + m_Offset,
			&value,
			sizeof(T)
		);
	}

	template<class T>
	inline std::optional<T> Property::Get(const void* instance) const {
		if (&m_Type != &GetType<T>()) {
			return {};
		}

		void* memoryLocation = ((char*)instance) + m_Offset;
		return *((T*)memoryLocation);
	}
}