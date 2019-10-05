#pragma once
//STD Headers

//Library Headers
#include <nlohmann/json.hpp>

//Void Engine Headers
#include "Resource.h"

namespace core {

class EntityData : public utils::Resource {
public:
	/**
	 * Constructor
	 */
	EntityData(const std::string& filepath);
	
	/**
	 * Loads resource from disk
	 */
	bool Load() override;

	/**
	 * Loads the resource's default value if the path provided is invalid
	 */
	virtual bool LoadErrorResource();

	/**
	 * Loads composite resources from main memory
	 */
	virtual void LoadComposite(utils::ResourceManager* manager);

	/**
	 * Allows the resource to be intialized after loading.
	 */
	virtual void Initialize();

private:
	nlohmann::json Data;
};

}
