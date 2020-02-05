#pragma once
//STD Headers

//Library Headers

//SuperVoid Headers
#include "core/gameplay_framework/Entity.h"

namespace SuperVoid {

	class BouncingCube : public core::Entity {
		TYPE_INFO_DECL(BouncingCube)

	public:
		/**
		 * Constructor
		 */
		BouncingCube();

		/**
		 * Destructor
		 */
		~BouncingCube() = default;

		/**
		 * Allows an entity to configure itself after it is constructed
		 */
		virtual void Initialize() override;

		/**
		 * Function that defines what the entity does once a level begins.
		 * @note This function largely acts like an initialization function
		 */
		void BeginPlay() override;

		/**
		 * Function that defines how an entity processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 */
		void Tick(float deltaSeconds) override;

		/**
		 * Defines entity death behaviors
		 */
		void Terminate() override;

	private:
		float Velocity;
	};

}