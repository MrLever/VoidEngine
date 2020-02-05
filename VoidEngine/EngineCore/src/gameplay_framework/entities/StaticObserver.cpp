//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/factory/Factory.h"

#include "gameplay_framework/entities/StaticObserver.h"

namespace core {
	TYPE_INFO_IMPL(StaticObserver)

	ENABLE_FACTORY(StaticObserver, Entity)

	StaticObserver::StaticObserver() {
	
	}

	void StaticObserver::Initialize() {
		Entity::Initialize();
	}

	void StaticObserver::BeginPlay() {
		;
	}

	void StaticObserver::Terminate() {
		;
	}

}
