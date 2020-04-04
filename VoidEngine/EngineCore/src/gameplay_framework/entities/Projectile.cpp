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

	Projectile::Projectile() {

	}

	Projectile::~Projectile() {

	}
	
	void Projectile::Initialize() {
		Entity::Initialize();
	}

	void Projectile::BeginPlay() {
		Entity::BeginPlay();
		static const float VELOCITY = 50.0f;
		auto physics = GetComponent<PhysicsComponent>();
		
		physics->AddVelocity(VELOCITY * m_Transform.GetForward());
	}

}
