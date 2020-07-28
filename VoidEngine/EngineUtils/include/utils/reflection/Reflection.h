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

namespace utils::reflection {
	template<typename T>
	concept IsReflectedClass = requires (T x) { T::s_TypeInfo; };

	template<typename T>
	concept IsReflectedPrimitive = requires (T x) { std::is_fundamental<T>::value == true; };

	template <typename T>
	requires IsReflectedPrimitive<T>
	inline const TypeDescriptor& GetPrimitiveTypeDescriptor() noexcept {
		static_assert(false, "Primitive type not reflected");
	}

	template<typename T>
	requires IsReflectedClass<T> || IsReflectedPrimitive<T>
	class TypeResolver {
	public:

		static const TypeDescriptor& GetType() {
			if constexpr (IsReflectedClass<T>) {
				return T::s_TypeInfo;
			}
			else if constexpr (IsReflectedPrimitive<T>) {
				return GetPrimitiveTypeDescriptor<T>();
			}
			else {
				static_assert(false, "Requested type not reflected");
			}
		}

		static const ClassDescriptor& GetClass() {
			if constexpr (IsReflectedClass<T>) {
				return T::s_TypeInfo;
			}
			else {
				static_assert(false, "Class reflection member inacessible.");
			}
		}
	};

} //namespace utils

//Defines used to annotate types to generate reflection data
#define CLASS(...) 
#define PROPERTY(...) 
#define CTOR(...) 
#define FUNCTION(...) 
#define ENABLE_RTTR() \
	static utils::ClassDescriptor s_TypeInfo;

//Defines used in reflection data generation
#define DECL_PROP(CLAZZ, TYPE, NAME) utils::Property{ utils::reflection::GetPrimitiveTypeDescriptor<TYPE>(), utils::Name(#NAME), offsetof(CLAZZ, NAME) }


#define IMPL_GET_TYPE(TYPE) \
	template<> \
	inline const utils::TypeDescriptor& utils::reflection::GetPrimitiveTypeDescriptor<TYPE>() noexcept { \
		static TypeDescriptor type{utils::Name(#TYPE), sizeof(TYPE)}; \
		return type; \
	}

IMPL_GET_TYPE(int)
IMPL_GET_TYPE(float)
IMPL_GET_TYPE(double)
IMPL_GET_TYPE(char)