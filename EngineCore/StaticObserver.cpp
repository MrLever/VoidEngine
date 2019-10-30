//STD Headers

//Library Headers

//Void Engine Headers
#include "StaticObserver.h"

namespace core {

	StaticObserver::StaticObserver(const utils::Name& name) : Entity(name) {
	
	}

	StaticObserver::StaticObserver(const std::string& name) : Entity(name) {
	
	}

	void StaticObserver::Initialize() {
		;
	}

	void StaticObserver::BeginPlay() {
		;
	}

	void StaticObserver::Terminate() {
		;
	}

}
