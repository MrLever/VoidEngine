//STD Headers

//Library Headers

//Void Engine Headers
#include "PhysicsComponent.h"

namespace core {
	ENABLE_FACTORY(PhysicsComponent, Component)

	PhysicsComponent::PhysicsComponent() : Velocity(), Force(), Mass(1), InverseMass(1),
		GravityScale(1), Density(1), Restitution(.5), IsStatic(false) {
		if (!IsStatic) {
			Mass = InverseMass = 0;
		}
	}

	PhysicsComponent::~PhysicsComponent() {

	}

	void PhysicsComponent::Initialize() {
		if (ComponentData.find("isStatic") != ComponentData.end()) {
			IsStatic = ComponentData["isStatic"].get<bool>();
		}
		if (ComponentData.find("mass") != ComponentData.end()) {
			Mass = ComponentData["mass"].get<float>();
			InverseMass = (Mass == 0.0f) ? 0 : 1 / Mass;
		}
		if (ComponentData.find("gravityScale") != ComponentData.end()) {
			GravityScale = ComponentData["gravityScale"].get<float>();
		}
		if (ComponentData.find("restitution") != ComponentData.end()) {
			Restitution = ComponentData["restitution"].get<float>();
		}
	}

	void PhysicsComponent::ApplyForce(const math::Vector3& force) {
		Force += force;
	}

	float PhysicsComponent::GetMass() const {
		return Mass;
	}

	float PhysicsComponent::GetInverseMass() const {
		return InverseMass;
	}

	math::Vector3 PhysicsComponent::GetForce() const {
		return Force;
	}

	void PhysicsComponent::ClearForce() {
		Force.X = Force.Y = Force.Z = 0;
	}

	math::Vector3 PhysicsComponent::GetVelocity() const {
		return Velocity;
	}

	void PhysicsComponent::AddVelocity(const math::Vector3& velocity) {
		Velocity += velocity;
	}

	float PhysicsComponent::GetRestitution() const {
		return Restitution;
	}

	float PhysicsComponent::GetGravityScale() const {
		return GravityScale;
	}

	bool PhysicsComponent::GetIsStatic() const {
		return IsStatic;
	}

	utils::Name PhysicsComponent::GetTypename() const {
		return utils::Name("PhysicsComponent");
	}

	utils::Name PhysicsComponent::GetStaticTypename() {
		return utils::Name("PhysicsComponent");
	}

}