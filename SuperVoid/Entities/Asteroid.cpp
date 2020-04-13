//STD Headers

//External Headers

//SuperVoid Headers
#include "Asteroid.h"

namespace SuperVoid {
	TYPE_INFO_IMPL(Asteroid)

	ENABLE_FACTORY(Asteroid, core::Entity)

	Asteroid::Asteroid() : Entity(), minScaleMagnitude(0.866025403784f) {

	}


	void Asteroid::Initialize() {
		Entity::Initialize();

		if (DataContainsKey("minScaleMagnitude")) {
			minScaleMagnitude = configData["minScaleMagnitude"];
		}
	}

	void Asteroid::Tick(float deltaSeconds) {
		Entity::Tick(deltaSeconds);

		math::Quaternion deltaRotation(math::Rotator(-1, 1, -1));
		transform.rotation *= deltaRotation;
	}

	void Asteroid::OnHit() {
		Destroy();
	}

	void Asteroid::OnDestroy() {
		if (transform.scale.Magnitude() / 2 < minScaleMagnitude) {
			return;
		}

		auto clone1 = GetWorld()->SpawnEntity(core::Prototype(configData), nullptr, transform);
		auto clone2 = GetWorld()->SpawnEntity(core::Prototype(configData), nullptr, transform);
		clone1->transform.position = transform.position + math::Vector3(0, 1.1f, 0);
		clone1->transform.scale = transform.scale * 0.5f;
		clone1->GetComponent<core::PhysicsComponent>()->AddVelocity({ 0 , 1, 0 });
		
		clone2->transform.position = transform.position + math::Vector3(0, -1.1f, 0);
		clone2->transform.scale = transform.scale * 0.5f;
		clone2->GetComponent<core::PhysicsComponent>()->AddVelocity({ 0, -1, 0 });
	}

}