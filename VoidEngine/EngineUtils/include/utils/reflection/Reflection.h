#pragma once
//STD Headers
#include <concepts>
#include <optional>

//Library Headers

//Void Engine Headers
#include "utils/Name.h"
#include "utils/reflection/TypeDescriptor.h"
#include "utils/reflection/ClassDescriptor.h"
#include "utils/reflection/Property.h"
#include "utils/reflection/Function.h"

namespace utils {

//Namespace to contain reflection api functions
namespace reflection { 
	/**
	 * Allow users to query for basic type properties, name and size
	 * @tparam T The type to aquire reflected data for.
	 */
	template<typename T>
	const TypeDescriptor& GetType() noexcept;

	/**
	 * Allow users to query advanced properties of non-built in types
	 * @tparam T The type to aquire reflected data for.
	 */
	template<typename T>
	const ClassDescriptor& GetClass();
} //namespace reflection

}

//Defines used to annotate types to generate reflection data
#define CLASS(...) 
#define PROPERTY(...) 
#define CTOR(...) 
#define FUNCTION(...) 


#define IMPL_GET_TYPE(TYPE) \
	template<>\
	const utils::TypeDescriptor& utils::reflection::GetType<TYPE>() noexcept { \
		static TypeDescriptor type{#TYPE, sizeof(TYPE)};\
		return type;\
	}

IMPL_GET_TYPE(int)
IMPL_GET_TYPE(char)
IMPL_GET_TYPE(bool)
IMPL_GET_TYPE(float)
IMPL_GET_TYPE(double)
IMPL_GET_TYPE(long)

template<>
const utils::TypeDescriptor& utils::reflection::GetType<void>() noexcept {
	static TypeDescriptor type{"void", 0}; 
	return type; 
}