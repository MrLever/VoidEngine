//STD Headers

//Library Headers

//Void Engine Headers
#include "utils\reflection\TypeDescriptor.h"

namespace utils {

	bool TypeDescriptor::operator==(const TypeDescriptor& other) const {
		return m_Name == other.m_Name && m_Size == other.m_Size;
	}

}