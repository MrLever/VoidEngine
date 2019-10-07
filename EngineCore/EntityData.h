#pragma once
//STD Headers

//Library Headers
#include <nlohmann/json.hpp>

//Void Engine Headers
#include "JsonResource.h"

namespace core {

class EntityData : public utils::JsonResource {
public:
	/**
	 * Constructor
	 */
	EntityData(const std::string& filepath);
	
	/**
	 * Destructor
	 */
	~EntityData() = default;
};

}
