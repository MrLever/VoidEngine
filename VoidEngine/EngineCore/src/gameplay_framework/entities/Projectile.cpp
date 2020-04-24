//STD Headers

//Library Headers

//Void Engine Headers
#include "gameplay_framework/entities/Projectile.h"
#include "physics/components/PhysicsComponent.h"
#include "physics/components/ColliderComponent.h"
#include "rendering/components/GraphicsComponent.h"

namespace core {
	TYPE_INFO_IMPL(Projectile)

	ENABLE_FACTORY(Projectile, Entity)

	Projectile::Projectile() : timeToLive(0.0f), useTimeToLive(false) {

	}

	Projectile::~Projectile() {

	}
	
	void Projectile::Initialize() {
		Entity::Initialize();

		if (configData.find("timeToLive") != configData.end()) {
			timeToLive = configData["timeToLive"];
			useTimeToLive = true;
		}
	}

	void Projectile::BeginPlay() {
		Entity::BeginPlay();
		static const float VELOCITY = 50.0f;
		auto physics = GetComponent<PhysicsComponent>();
		
		physics->AddVelocity(VELOCITY * GetForward());
	}

	void Projectile::Tick(float deltaTime) {
		Entity::Tick(deltaTime);

		//TODO: Replace with coroutine
		if (useTimeToLive) {
			timeToLive -= deltaTime;
			if (timeToLive < 0) {
				this->Destroy();
			}
		}

	}

	void Projectile::OnHit() {
		Destroy();
	}

}
