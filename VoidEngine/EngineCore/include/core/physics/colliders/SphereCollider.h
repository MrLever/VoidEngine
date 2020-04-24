#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/physics/colliders/Collider.h"
#include "core/physics/components/ColliderComponent.h"

namespace core {

	class SphereCollider : public Collider {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(SphereCollider)

	public:
		/**
		 * Constructor
		 */
		SphereCollider();

		/**
		 * Destructor
		 */
		~SphereCollider() override;
		
		/**
		 * Set's up sphere collision volume
		 */
		void Initialize() override;
		
		/** 
		 * Radius Accessor 
		 */
		float GetRadius() const;

		/**
		 * Defines how to draw collision volume
		 */
		void Draw(std::shared_ptr<ShaderProgram> shader, const glm::mat4& transform);

	private:
		/** Radius of the collision sphere */
		float Radius;

	};

}

