#pragma once
//STD Headers

//Library Headers

//Void Engine Headers

/**
 * @struct TypeName
 * @brief TypeName is a templated structure used to stringify typenames.
 * @note Default behavior is to use std C++ typeinfo. The string returned by 
 *       by this defualt implementation is compiler dependent, and not guarenteed
 *       to be unique. 
 * @note Users can specialize this template to be implementation independent 
 *       using the ENABLE_TYPENAME macro
 */
template <typename T>
struct TypeName {
	static const char* GetName() {
		return typeid(T).name();
	}
};

#define ENABLE_TYPENAME(A) template<> struct TypeName<A> { static constexpr const char* GetName() { return #A; }};