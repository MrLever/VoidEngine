#pragma once
//STD Headers
#include <concepts>

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
	 * @brief A named member of a type
	 */
	struct Property {
		/** The type of the class member */
		const Type& m_Type;

		/** The name of the class memeber */
		utils::Name m_Name;

		/** The offset of the class member in memory */
		size_t m_Offset;

		template<class T>
		void Set(void* instance, const T& value) {
			//assert(m_Type == GetType<T>());

			memcpy(
				((char*) instance) + m_Offset, 
				&value, 
				sizeof(T)
			);
		}

		template<class T>
		T Get(const void* instance) const {
			//assert(m_Type == GetType<T>());

			void* memoryLocation = ((char*)instance) + m_Offset;
			return *((T*)memoryLocation);
		}

	};

	struct Function {
		Property m_ReturnValue;
		std::vector<Property> m_Params;
		utils::Name m_Name;
	};

	struct Class : public Type {
		std::vector<Property> m_Properties;
		std::vector<Function> m_Functions;

		template<typename T>
		void SetProperty(void* instance, const utils::Name& name, const T& value) {
			for (auto& property : m_Properties) {
				if (property.m_Name == name) {
					property.Set(instance, value);
					break;
				}
			}
		}

		template<typename T>
		T GetProperty(const void* instance, const utils::Name& name) const {
			for (auto& property : m_Properties) {
				if (property.m_Name == name) {
					return property.Get<T>(instance);
				}
			}
		}
	};

	template<typename T>
	const Type& GetType() noexcept;

	template<typename T>
	const Class& GetClass();

	#define IMPL_GET_TYPE(TYPE) \
	template<>\
	const Type& GetType<TYPE>() noexcept { \
		static Type type{#TYPE, sizeof(TYPE)};\
		return type;\
	}

	IMPL_GET_TYPE(bool)
	IMPL_GET_TYPE(int)
	IMPL_GET_TYPE(unsigned int)
	IMPL_GET_TYPE(long)
	IMPL_GET_TYPE(float)
	IMPL_GET_TYPE(double)
}

//Defines used to annotate types to generate reflection data
#define CLASS(...) 
#define PROPERTY(...) 
#define CTOR(...) 
#define FUNCTION(...) 