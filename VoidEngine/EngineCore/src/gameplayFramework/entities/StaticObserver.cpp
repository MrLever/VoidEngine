//STD Headers

//Library Headers

//Void Engine Headers
#include "StaticObserver.h"
#include "utils/factory/Factory.h"

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
