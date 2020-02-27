#pragma once
//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "math/Vector.h"

#include "utils/factory/Factory.h"
#include "utils/factory/FactoryConstructible.h"

#include "core/rendering/ShaderProgram.h"

namespace core {
	
	class Collider : public utils::FactoryConstructible {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(Collider)

	public:
		/**
		 * Constructor
		 */
		Collider();

		/**
		 * Applies configuration settings
		 */
		virtual void Initialize() = 0;

		/**
		 * Defines how to draw collision volume
		 */
		virtual void Draw(std::shared_ptr<ShaderProgram> shader, const glm::mat4& transform) = 0;

	};

}

