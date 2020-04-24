#pragma once
//STD Headers
#include <unordered_set>

//Library Headers

//SuperVoid Headers
#include "Asteroid.h"

namespace SuperVoid {

	class AsteroidEmitter : public core::Entity {
		TYPE_INFO_DECL(AsteroidEmitter)

	public:
		/**
		 * Constructor
		 */
		AsteroidEmitter();

		/**
		 * Destructor
		 */
		~AsteroidEmitter() = default;

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

		/**
		 * Spawns an asteroid at a random orientation/speed
		 */
		void SpawnWave();

		/**
		 * Adds an asteroid to the emitter for tracking
		 */
		void RegisterAsteroid(Asteroid* newAsteroid);

		/**
		 * Removes asteroid from the asteroid set
		 */
		void UnregisterAsteroid(Asteroid* deadAsteroid);

	private:
		Entity* player;
		std::unordered_set<Entity*> asteroids;
		core::Prototype asteroidPrefab;
		
		int minAsteroids;
		int maxAsteroids;

		std::mt19937 randomNumberGenerator;
		int seed;
	};

}