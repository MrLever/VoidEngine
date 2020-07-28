//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/reflection/TypeDescriptor.h"

namespace utils {
	
	std::unordered_map<utils::Name, TypeDescriptor&> TypeDescriptor::s_TypeRegistry;

	TypeDescriptor::TypeDescriptor(const utils::Name& name, size_t size) : m_Name(name), m_Size(size) {
		//s_TypeRegistry.insert({ m_Name, *this });
	}

	bool TypeDescriptor::operator==(const TypeDescriptor& other) const {
		return m_Name == other.m_Name && m_Size == other.m_Size;
	}

}