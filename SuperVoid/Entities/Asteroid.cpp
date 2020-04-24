//STD Headers
#include <random>

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
		
		if (std::abs(transform.position.X) > 75) {
			transform.position.X *= -1;
		}

		if (std::abs(transform.position.Y) > 75) {
			transform.position.Y *= -1;
		}

		transform.rotation *= deltaRotation;
	}

	void Asteroid::OnHit() {
		Destroy();
	}

	void Asteroid::OnDestroy() {
		if (transform.scale.Magnitude() / 2 < minScaleMagnitude) {
			return;
		}
		
		//Generate spawn angle
		std::mt19937 randomNumberGenerator;
		randomNumberGenerator.seed(std::random_device()());
		std::uniform_real_distribution<float> dist(0.0, 180.0f);
		float spawnAngle = dist(randomNumberGenerator);
		math::Quaternion spawnRotation(math::Rotator(0, 0, spawnAngle));

		//Calculate new velocy
		auto currVelocity = GetComponent<core::PhysicsComponent>()->GetVelocity();
		auto cloneVelocityMag = currVelocity.Magnitude() * 1.25f;
		auto cloneVelocity = spawnRotation.Rotate(math::Vector3(1, 0, 0)) * cloneVelocityMag;

		//Spawn clones
		auto clone1 = GetWorld()->SpawnEntity(core::Prototype(configData), transform);
		auto clone2 = GetWorld()->SpawnEntity(core::Prototype(configData), transform);
		
		//Configure clones
		clone1->transform.scale = transform.scale * 0.5f;
		clone1->GetComponent<core::PhysicsComponent>()->AddVelocity(cloneVelocity);
		
		clone2->transform.scale = transform.scale * 0.5f;
		clone2->GetComponent<core::PhysicsComponent>()->AddVelocity(-cloneVelocity);
	}

}