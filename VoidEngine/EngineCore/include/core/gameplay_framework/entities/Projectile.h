#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/gameplay_framework/Entity.h"

namespace core {

	class Projectile : public Entity {
		TYPE_INFO_DECL(Projectile)

	public:
		/**
		 * Constructor
		 */
		Projectile();

		/**
		 * Destructor
		 */
		~Projectile() override;

		/**
		 * Attatches Physics, Collider, and Graphics component to projectile
		 */
		void Initialize() override;

		/**
		 * Gives projectile basic trajectory
		 */
		void BeginPlay() override;

	};

}

