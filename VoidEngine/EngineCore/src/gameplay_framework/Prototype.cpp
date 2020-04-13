#include "..\..\include\core\gameplay_framework\Prototype.h"
//STD Headers

//Library headers

//Void Engine Headers

namespace core {

	Prototype::Prototype(const nlohmann::json& data) : m_Data(data) {

	}

	const nlohmann::json& Prototype::GetData() const {
		return m_Data;
	}

}