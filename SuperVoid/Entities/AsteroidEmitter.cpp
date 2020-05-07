//STD Headers
#include <random>

//Library Headers

//SuperVoid Headers
#include "core/Scene.h"
#include "AsteroidEmitter.h"
#include "Asteroid.h"

namespace SuperVoid {

	ENABLE_FACTORY(AsteroidEmitter, core::Entity)

	AsteroidEmitter::AsteroidEmitter() 
		: player(nullptr), minAsteroids(10), maxAsteroids(20), randomNumberGenerator(std::random_device()()), seed(-1){

	}

	void AsteroidEmitter::Initialize() {
		Entity::Initialize();
		if (configData.find("asteroidPrefab") != configData.end()) {
			asteroidPrefab = core::Prototype(configData["asteroidPrefab"]);
		}

		if (configData.find("seed") != configData.end()) {
			seed = configData["seed"];
			randomNumberGenerator.seed(seed);
		}

		if (configData.find("playerRef") != configData.end()) {
			player = GetWorld()->FindEntityByID(configData["playerRef"]);
		}

		if (configData.find("minAsteroids") != configData.end()) {
			minAsteroids = configData["minAsteroids"];
		}

		if (configData.find("maxAsteroids") != configData.end()) {
			maxAsteroids = configData["maxAsteroids"];
		}
	}

	void AsteroidEmitter::BeginPlay() {
		utils::Logger::LogInfo(name.StringID + " began play");
		SpawnWave();
	}

	void AsteroidEmitter::Tick(float deltaSeconds) {
		if (asteroids.size() == 0) {
			minAsteroids++;
			maxAsteroids++;
			SpawnWave();
		}
	}

	void AsteroidEmitter::Terminate() {

	}

	void AsteroidEmitter::SpawnWave() {
		std::uniform_int_distribution asteroidCountDist(minAsteroids, maxAsteroids);
		std::uniform_int_distribution asteroidSizeDist(2, 8);
		std::uniform_real_distribution<float> spawnAngleDist(0.0, 360.0f);
		std::uniform_real_distribution<float> spawnRadiusDist(24, 64);
		std::uniform_real_distribution<float> spawnVelocityDist(5, 20);

		int numToSpawn = asteroidCountDist(randomNumberGenerator);
		utils::Logger::LogInfo("Spawning " + std::to_string(numToSpawn) + " asteroids.");
		
		for (int i = 0; i < numToSpawn; i++) {
			core::Transform asteroidTransform;

			//Calculate asteroid properties
			math::Quaternion spawnAngle(math::Rotator(0, 0, spawnAngleDist(randomNumberGenerator)));
			float spawnDistance = spawnRadiusDist(randomNumberGenerator);

			math::Vector3 spawnTranslationVector = spawnAngle.Rotate(math::Vector3(1, 0, 0));
			spawnTranslationVector *= spawnDistance;

			asteroidTransform.position = player->GetPosition() + spawnTranslationVector;
			asteroidTransform.scale *= (float)asteroidSizeDist(randomNumberGenerator);

			//Spawn asteroid
			auto asteroid = dynamic_cast<Asteroid*>(
				GetWorld()->SpawnEntity(asteroidPrefab, asteroidTransform)
			);
			asteroid->RegisterEmitter(this);
			asteroids.insert(asteroid);

			//Apply initial conditions
			auto asteroidRigidBody = asteroid->GetComponent<core::PhysicsComponent>();
			asteroidRigidBody->AddVelocity(
				math::Quaternion(math::Rotator(0, 0, spawnAngleDist(randomNumberGenerator)))
				.Rotate({ 1,0,0 }) *
				spawnVelocityDist(randomNumberGenerator)
			);

		}

		if (player == nullptr) {
			utils::Logger::LogError("Asteroid emmitter doesn't know where the player is. Cannot safely spawn asteroids");
			return;
		}
	}

	void AsteroidEmitter::RegisterAsteroid(Asteroid* newAsteroid) {
		asteroids.insert(newAsteroid);
	}

	void AsteroidEmitter::UnregisterAsteroid(Asteroid* deadAsteroid) {
		if (asteroids.find(deadAsteroid) != asteroids.end()) {
			asteroids.erase(deadAsteroid);
		}
	}
}