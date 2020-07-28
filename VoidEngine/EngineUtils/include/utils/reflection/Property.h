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
		template<class T, class InstanceType>
		void SetValue(InstanceType* instance, const T& value);

		/**
		 * Allows user to access a property through it's reflection data
		 * @param instance The pointer to the class instance that holds this property
		 */
		template<class T, class InstanceType>
		std::optional<T> GetValue(const InstanceType* instance) const;

	};

	template<class T, class InstanceType>
	inline void Property::SetValue(InstanceType* instance, const T& value) {
		//Assert that the template type matches the actual type of this property
		assert(m_Type == reflection::TypeResolver<T>::GetType());

		//Avoid memcpy to ensure assignment operator for type T is called.
		T* propertyMemoryPtr = (T*)(((char*)instance) + m_Offset);
		*propertyMemoryPtr = value;
	}

	template<class T, class InstanceType>
	inline std::optional<T> Property::GetValue(const InstanceType* instance) const {
		if (m_Type != reflection::TypeResolver<T>::GetType()) {
			return {};
		}

		T* propertyMemoryPtr = (T*)(((char*)instance) + m_Offset);
		return *propertyMemoryPtr;
	}
}