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

		Position = Parent->GetPostion() + (5 * Parent->GetRotation().ToVector());

		AddComponent(new PhysicsComponent());

		auto collider = new ColliderComponent();
		nlohmann::json colliderConfig = 
		{
			{
				"type","ColliderComponent"
			},
			{
				"shape", {
					{
						"type","SphereCollider"
					},
					{
						"radius", 0.25f
					}
				}
			}
		};
		collider->SetConfigData(colliderConfig);
		AddComponent(collider);

		auto model = new GraphicsComponent();
		nlohmann::json graphicsData = 
		{
			{"model","Resources/Models/Projectile/Projectile.obj"}
		};
		model->SetConfigData(graphicsData);
		AddComponent(model);


		//Initialize all components
		Entity::Initialize();
	}

	void Projectile::BeginPlay() {
		static const float VELOCITY = 50.0f;
		auto physics = GetComponent<PhysicsComponent>();

		physics->AddVelocity(VELOCITY * Parent->GetRotation().ToVector());
	}

}
