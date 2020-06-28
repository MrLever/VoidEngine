#pragma once
//STD Headers
#include <concepts>
#include <optional>

//Library Headers

//Void Engine Headers
#include "utils/Name.h"
#include "utils/reflection/Type.h"
#include "utils/reflection/Class.h"
#include "utils/reflection/Property.h"

namespace utils {

	struct Function {
		Property m_ReturnValue;
		std::vector<Property> m_Params;
		utils::Name m_Name;
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