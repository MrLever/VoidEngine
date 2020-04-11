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
		auto clone1 = GetWorld()->SpawnEntity(core::Prototype(configData), nullptr, transform);
		auto clone2 = GetWorld()->SpawnEntity(core::Prototype(configData), nullptr, transform);
		clone1->transform.position = transform.position + math::Vector3(0, 1.1f, 0);
		clone1->GetComponent<core::PhysicsComponent>()->AddVelocity({ 0 , 1, 0 });
		
		clone2->transform.position = transform.position + math::Vector3(0, -1.1f, 0);
		clone2->GetComponent<core::PhysicsComponent>()->AddVelocity({ 0, -1, 0 });
	}

}