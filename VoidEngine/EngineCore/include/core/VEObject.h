#pragma once
//STD Headesr

//Library Headers

//Void Engine Headers
#include "utils/TypeUtils.h"

namespace core {
	
	/**
	 * Base class for all runtime objects passed around the engine that need custom RTTI support
	 */
	class VEObject {
		TYPE_INFO_BASE_DECL(VEObject);

	public:
		VEObject() = default;
		virtual ~VEObject() = default;

	};

}