//STD Headers

//External Headers

//SuperVoid Headers
#include "Asteroid.h"

namespace SuperVoid {
	TYPE_INFO_IMPL(Asteroid)

	ENABLE_FACTORY(Asteroid, core::Entity)

	Asteroid::Asteroid() : Entity() {
	
	}


	void Asteroid::OnHit() {
		Destroy();
	}

	void Asteroid::OnDestroy() {
		auto clone1 = GetWorld()->SpawnEntity(core::Prototype(ConfigData), nullptr, transform);
		auto clone2 = GetWorld()->SpawnEntity(core::Prototype(ConfigData), nullptr, transform);

		clone1->GetComponent<core::PhysicsComponent>()->AddVelocity({ 0 , 1, 0 });
		clone2->GetComponent<core::PhysicsComponent>()->AddVelocity({ 0, -1, 0 });
	}

}