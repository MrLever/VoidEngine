//STD Headers
#include <random>

//Library Headers

//SuperVoid Headers
#include "core/Scene.h"
#include "AsteroidEmitter.h"
#include "Asteroid.h"

namespace SuperVoid {

	TYPE_INFO_IMPL(AsteroidEmitter)

	ENABLE_FACTORY(AsteroidEmitter, core::Entity)

	AsteroidEmitter::AsteroidEmitter() 
		: minAsteroids(10), maxAsteroids(20), randomNumberGenerator(std::random_device()()), seed(-1){

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
	}

	void AsteroidEmitter::BeginPlay() {
		utils::Logger::LogInfo(name.StringID + " began play");
		SpawnWave();
	}

	void AsteroidEmitter::Tick(float deltaSeconds) {

	}

	void AsteroidEmitter::Terminate() {

	}

	void AsteroidEmitter::SpawnWave() {
		std::uniform_int_distribution distribution(minAsteroids, maxAsteroids);
		std::uniform_int_distribution sizeDist(1, 8);

		int numToSpawn = distribution(randomNumberGenerator);
		utils::Logger::LogInfo("Spawning " + std::to_string(numToSpawn) + " asteroids.");
		
		float x = -24, y = 5;
		for (int i = 0; i < numToSpawn; i++) {
			int size = sizeDist(randomNumberGenerator);
			core::Transform asteroidTransform;
			asteroidTransform.position = { x, y, 0 };
			x += 8;
			asteroidTransform.scale *= (float)size;

			auto asteroid = GetWorld()->SpawnEntity(asteroidPrefab, asteroidTransform);
		}

		if (player == nullptr) {
			utils::Logger::LogError("Asteroid emmitter doesn't know where the player is. Cannot safely spawn asteroids");
			return;
		}
	}
}