#pragma once
//STD Headers

//External Headers
#include <core/Scene.h>
#include <core/gameplay_framework/Entity.h>
#include <math/Vector.h>

//SuperVoid Headers

namespace SuperVoid {
	class AsteroidEmitter;

	class Asteroid : public core::Entity {
		ENABLE_RTTI(Asteroid)

	public:
		/**
		 * Constructor
		 */
		Asteroid();

		/**
		 * Destructor
		 */
		~Asteroid() = default;

		/**
		 * Initialize member variables
		 */
		void Initialize() override;

		/**
		 * Registers this asteroid to an emitter
		 */
		void BeginPlay() override;

		/**
		 * Rotates asteroid
		 */
		void Tick(float deltaSeconds) override;

		/**
		 * Causes asteroid to split
		 */
		void OnHit() override;

		/**
		 * Spawns two child asteroids
		 */
		void OnDestroy() override;

		/**
		 * Allows parent emitter to pass a reference to the asteroid
		 */
		void RegisterEmitter(AsteroidEmitter* emitter);

	private:
		float minScaleMagnitude;
		AsteroidEmitter* emitter;
	};
}