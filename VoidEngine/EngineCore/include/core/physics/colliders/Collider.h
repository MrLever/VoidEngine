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
		ENABLE_RTTI(Collider)

	public:
		/**
		 * Constructor
		 */
		Collider();

		/**
		 * Destructor
		 */
		virtual ~Collider() = default;

		/**
		 * Applies configuration settings
		 */
		virtual void Initialize() = 0;

		/**
		 * Apply entity scale data
		 */
		void SupplyEntityScale(const math::Vector3& entityScale);

		/**
		 * Defines how to draw collision volume
		 */
		virtual void Draw(std::shared_ptr<ShaderProgram> shader, const glm::mat4& transform) = 0;

	protected:
		const math::Vector3* entityScale;

	};

}

