#pragma once
//STD Headers
#include <functional>

//Library Headers

//Void Engine Headers
#include "Component.h"
#include "Collider.h"
#include "Table.h"
#include "Manifold.h"

namespace core {

	enum class CollisionLayer : unsigned {
		NONE = 0x00,
		WORLD = 0x01,
		ENTITY = 0x02,
		PLAYER = 0x04,
		ALL = std::numeric_limits<unsigned>::max()
	};

	class ColliderComponent : public Component {
	public:
		/**
		 * Constructor
		 */
		ColliderComponent();

		/**
		 * Returns name of dynamic Component Type
		 */
		utils::Name GetTypename() const override;

		/**
		 * Returns name of static Component Type
		 */
		static utils::Name GetStaticTypename();

		/**
		 * Sets up collider data from ComponentData
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

		/** Accessor for shape */
		const Collider* GetShape() const;

		template <class ColliderA, class ColliderB>
		static void RegisterCollisionCallback(std::function<Manifold*(ColliderComponent*, ColliderComponent*)> callback);

	protected:
		static utils::Table
			<utils::Name, utils::Name, std::function<Manifold*(ColliderComponent*, ColliderComponent*)>>
		CollisionJumpTable;

		/** Layer(s) this collider interacts with */
		unsigned Layer;

		/** The type of shape used when resolving collisions with this component */
		Collider* Shape;
	
	};

	template<class ColliderA, class ColliderB>
	inline void ColliderComponent::RegisterCollisionCallback(
		std::function<Manifold*(ColliderComponent*, ColliderComponent*)> callback
	) {
		utils::Name i(TypeName<ColliderA>::GetName());
		utils::Name j(TypeName<ColliderB>::GetName());
		if (CollisionJumpTable.Find(i, j) != nullptr) {
			utils::Logger::LogWarning(
				"CollisionCallback [" +
				i.StringID + "][" +
				j.StringID + "] has already been registered");
			return;
		}

		CollisionJumpTable[i][j] = callback;
	}

}

