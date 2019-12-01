//STD Headers

//Library Headers

//Void Engine Headers
#include "AABBCollider.h"

namespace core {

	ENABLE_FACTORY(AABBCollider, Collider)

	bool AABBCollider::CallbacksRegistered = false;

	AABBCollider::AABBCollider() {
		if (!CallbacksRegistered) {
			ColliderComponent::RegisterCollisionDetectionCallback
				<AABBCollider, AABBCollider>(DetectAABBCollision);

			CallbacksRegistered = true;
		}
	}

	void AABBCollider::Initialize() {
		MinExtent.X = ShapeData["min"][0].get<float>();
		MinExtent.Y = ShapeData["min"][1].get<float>();
		MinExtent.Z = ShapeData["min"][2].get<float>();

		MaxExtent.X = ShapeData["max"][0].get<float>();
		MaxExtent.Y = ShapeData["max"][1].get<float>();
		MaxExtent.Z = ShapeData["max"][2].get<float>();
	}

	Manifold* AABBCollider::DetectAABBCollision(ColliderComponent* left, ColliderComponent* right) {
		const AABBCollider* aabb1 = reinterpret_cast<const AABBCollider*>(left->GetShape());
		const AABBCollider* aabb2 = reinterpret_cast<const AABBCollider*>(right->GetShape());

		auto aabb1Pos = left->GetPosition();
		auto aabb2Pos = right->GetPosition();

		auto translationVector = aabb2Pos - aabb1Pos;

		//SAT- Project onto x axis
		float xWidth1 = (aabb1->GetMax().X - aabb1->GetMin().X) / 2;
		float xWidth2 = (aabb1->GetMax().X - aabb1->GetMin().X) / 2;

		float xOverlap = xWidth1 + xWidth2 - std::abs(translationVector.X);
		if (xOverlap < 0) {
			//X axis is separating axis
			return nullptr;
		}

		//SAT- Project onto y axis
		float yWidth1 = (aabb1->GetMax().Y - aabb1->GetMin().Y) / 2;
		float yWidth2 = (aabb1->GetMax().Y - aabb1->GetMin().Y) / 2;

		float yOverlap = yWidth1 + yWidth2 - std::abs(translationVector.Y);
		if (yOverlap < 0) {
			//Y axis is separating axis
			return nullptr;
		}
		
		//SAT- Project onto z axis
		float zWidth1 = (aabb1->GetMax().Z - aabb1->GetMin().Z) / 2;
		float zWidth2 = (aabb1->GetMax().Z - aabb1->GetMin().Z) / 2;

		float zOverlap = zWidth1 + zWidth2 - std::abs(translationVector.Z);
		if (zOverlap < 0) {
			//Z axis is separating axis
			return nullptr;
		}
		
		//No separating axis found
		auto manifold = new Manifold();
		manifold->ColliderA = left;
		manifold->ColliderB = right;

		//At this point it is certain there is no separating axis, the objects are colliding
		//Find smallest axis of seperation
		if (xOverlap < yOverlap && yOverlap <= zOverlap) {
			manifold->PenetrationDistance = xOverlap;
			auto xAxis = math::Vector3(1, 0, 0);
			if (translationVector.X < 0) {
				xAxis *= -1;
			}
			manifold->CollisionNormal = xAxis;
		}
		else if (yOverlap <= zOverlap && zOverlap <= xOverlap) {
			//Allow for equal in this case to default to resolving collisions upward
			manifold->PenetrationDistance = yOverlap;
			auto yAxis = math::Vector3(0, 1, 0);
			if (translationVector.Y < 0) {
				yAxis *= -1;
			}
			manifold->CollisionNormal = yAxis;
		}
		else if (zOverlap < xOverlap && xOverlap <= yOverlap) {
			manifold->PenetrationDistance = zOverlap;
			auto zAxis = math::Vector3(0, 0, 1);
			if (translationVector.Z < 0) {
				zAxis *= -1;
			}
			manifold->CollisionNormal = zAxis;
		}

		return manifold;
	}

	math::Vector3 AABBCollider::GetMin() const {
		return MinExtent;
	}

	math::Vector3 AABBCollider::GetMax() const {
		return MaxExtent;
	}

	utils::Name AABBCollider::GetTypename() const {
		return utils::Name("AABBCollider");
	}

	utils::Name AABBCollider::GetStaticTypename() {
		return utils::Name("AABBCollider");
	}

}
