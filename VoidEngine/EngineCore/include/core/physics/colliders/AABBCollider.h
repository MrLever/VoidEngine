#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/physics/colliders/Collider.h"
#include "core/physics/components/ColliderComponent.h"

#include "core/rendering/VertexArray.h"


namespace core {

	class AABBCollider : public Collider {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(AABBCollider)

	public:
		/**
		 * Constructor
		 */
		AABBCollider();

		/**
		 * Applies configuration settings
		 */
		void Initialize() override;

		/**
		 * Defines how to draw collision volume
		 */
		void Draw(std::shared_ptr<ShaderProgram> shader, const glm::mat4& transform) override;

		/**
		 * Min extent accessor
		 */
		math::Vector3 GetMin() const;

		/**
		 * Min extent accessor
		 */
		math::Vector3 GetMax() const;

	private:
		/** The Min value of the AABB */
		math::Vector3 minExtent;

		/** The Max Value of the AABB */
		math::Vector3 maxExtent;

	};

}
