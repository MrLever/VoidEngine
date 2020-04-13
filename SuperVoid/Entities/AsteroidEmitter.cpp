//STD Headers

//Library Headers

//SuperVoid Headers
#include "core/Scene.h"
#include "AsteroidEmitter.h"
#include "Asteroid.h"

namespace SuperVoid {

	TYPE_INFO_IMPL(AsteroidEmitter)

	ENABLE_FACTORY(AsteroidEmitter, core::Entity)

	AsteroidEmitter::AsteroidEmitter() {

	}

	void AsteroidEmitter::Initialize() {
		Entity::Initialize();

	}

	void AsteroidEmitter::BeginPlay() {
		utils::Logger::LogInfo(name.StringID + " began play");
	}

	void AsteroidEmitter::Tick(float deltaSeconds) {

	}

	void AsteroidEmitter::Terminate() {

	}

	void AsteroidEmitter::SpawnAsteroid() {
		//GetWorld()->SpawnEntity<Asteroid>();
	}
}