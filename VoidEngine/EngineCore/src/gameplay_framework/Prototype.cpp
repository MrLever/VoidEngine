#include "..\..\include\core\gameplay_framework\Prototype.h"
//STD Headers

//Library headers

//Void Engine Headers

namespace core {

	Prototype::Prototype(nlohmann::json& data) : m_Data(std::move(data)) {

	}

	const nlohmann::json& Prototype::GetData() const {
		return m_Data;
	}

}