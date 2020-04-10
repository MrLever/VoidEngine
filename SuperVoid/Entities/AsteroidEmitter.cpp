//STD Headers

//Library Headers

//SuperVoid Headers
#include "core/Scene.h"
#include "AsteroidEmitter.h"
#include "Asteroid.h"

namespace SuperVoid {

	TYPE_INFO_IMPL(AsteroidEmitter)

	ENABLE_FACTORY(AsteroidEmitter, core::Entity)

	AsteroidEmitter::AsteroidEmitter() : m_SpawnTime(3.0f), m_TimeWaiting(0.0f) {

	}

	void AsteroidEmitter::Initialize() {
		Entity::Initialize();

		if (configData.find("spawnTime") != configData.end()) {
			m_SpawnTime = configData["spawnTime"];
		}
	}

	void AsteroidEmitter::BeginPlay() {
		utils::Logger::LogInfo(name.StringID + " began play");
	}

	void AsteroidEmitter::Tick(float deltaSeconds) {
		if (m_TimeWaiting >= m_SpawnTime) {
			m_TimeWaiting = 0;
			SpawnAsteroid();
		}
	}

	void AsteroidEmitter::Terminate() {

	}

	void AsteroidEmitter::SpawnAsteroid() {
		float minSpeed = 1.0f;
		float maxSpeed = 5.0f;
		//GetWorld()->SpawnEntity<Asteroid>();
	}
}