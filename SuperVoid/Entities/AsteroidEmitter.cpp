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

		if (ConfigData.find("spawnTime") != ConfigData.end()) {
			m_SpawnTime = ConfigData["spawnTime"];
		}
	}

	void AsteroidEmitter::BeginPlay() {
		utils::Logger::LogInfo(m_Name.StringID + " began play");
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