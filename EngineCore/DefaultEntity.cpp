//STD Headers

//Library Headers

//Void Engine Headers
#include "DefaultEntity.h"

namespace core {

	ENABLE_FACTORY(DefaultEntity, Entity)

	DefaultEntity::DefaultEntity() {
		
	}

	DefaultEntity::~DefaultEntity() {

	}

	void DefaultEntity::Initialize() {
		Entity::Initialize();
	}
	
	void DefaultEntity::BeginPlay() {
		;
	}

	void DefaultEntity::Tick(float deltaSeconds) {
		;
	}

	void DefaultEntity::Terminate() {
		;
	}
}