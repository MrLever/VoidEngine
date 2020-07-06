#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Name.h"

namespace utils {
	struct TypeDescriptor;

	template<class C, typename T>
	struct PropertyData {
		T C::* m_Data;

		T GetData(const C& instance) const { return instance.*m_Data;  }
	};

	/**
	 * @struct Propery
	 * @brief A named member of a derived or user defined type
	 */
	struct Property {
		/** The type of the class member */
		const TypeDescriptor& m_Type;

		/** The name of the class memeber */
		const utils::Name m_Name;

		/** The offset of the class member in memory */
		const size_t m_Offset;

		/**
		 * Allows user to modify instance of a property through it's reflection data
		 * @param instance The pointer to the class instance that holds this property
		 */
		template<class T>
		void SetValue(void* instance, const T& value);

		/**
		 * Allows user to access a property through it's reflection data
		 * @param instance The pointer to the class instance that holds this property
		 */
		template<class T>
		std::optional<T> GetValue(const void* instance) const;

	};

	template<class T>
	inline void Property::SetValue(void* instance, const T& value) {
		//Assert that the template type matches the actual type of this property
		assert(m_Type == reflection::GetType<T>());

		std::memcpy(
			((char*)instance) + m_Offset,
			&value,
			sizeof(T)
		);
	}

	template<class T>
	inline std::optional<T> Property::GetValue(const void* instance) const {
		if (m_Type != reflection::GetType<T>()) {
			return {};
		}

		void* memoryLocation = ((char*)instance) + m_Offset;
		return *((T*)memoryLocation);
	}
}