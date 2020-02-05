#pragma once
//STD Headers
#include <functional>

//Library Headers

//Void Engine Headers
#include "utils/Table.h"

#include "core/gameplay_framework/Component.h"
#include "core/physics/Manifold.h"
#include "core/physics/colliders/Collider.h"

namespace core {

	class ColliderComponent : public Component {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(ColliderComponent)

	public:
		/**
		 * Constructor
		 */
		ColliderComponent();

		/**
		 * Sets up collider data from ConfigData
		 */
		void Initialize() override;

		/**
		 * Allows the ColliderComponent to track the parent's position
		 * @param deltaSeconds the time elapsed since the previous tick
		 */
		virtual void Tick(float deltaTime) override;

		/**
		 * Functions to allow derived colliders to interact properly
		 * with other colliders
		 */
		Manifold* DetectCollision(ColliderComponent* other);

		/** 
		 * Accessor for shape 
		 */
		const Collider* GetShape() const;

		/**
		 * Accessor for CollisionLayer
		 */
		unsigned GetCollisionLayer() const;

		template <class ColliderA, class ColliderB>
		static void RegisterCollisionDetectionCallback(std::function<Manifold*(ColliderComponent*, ColliderComponent*)> callback);
		
	protected:
		static utils::Table
			<utils::Name, utils::Name, std::function<Manifold*(ColliderComponent*, ColliderComponent*)>>
		CollisionDetectionJumpTable;

		/** Layer(s) this collider interacts with */
		unsigned CollisionLayer;

		/** The type of shape used when resolving collisions with this component */
		Collider* Shape;
	
	};

	template<class ColliderA, class ColliderB>
	inline void ColliderComponent::RegisterCollisionDetectionCallback(
		std::function<Manifold*(ColliderComponent*, ColliderComponent*)> callback
	) {
		utils::Name i(ColliderA::GetStaticTypename());
		utils::Name j(ColliderB::GetStaticTypename());
		if (CollisionDetectionJumpTable.Find(i, j) != nullptr) {
			utils::Logger::LogWarning(
				"Collision Detection Callback [" +
				i.StringID + "][" +
				j.StringID + "] has already been registered");
			return;
		}

		CollisionDetectionJumpTable[i][j] = callback;
	}

}

