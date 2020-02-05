#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/gameplay_framework/Component.h"

namespace core {

	class PhysicsComponent : public Component {
		/**
		* Declare custom RTTI support
		*/
		TYPE_INFO_DECL(PhysicsComponent)

	public:
		/**
		 * Constructor
		 */
		PhysicsComponent();

		/**
		 * Destructor
		 */
		~PhysicsComponent();

		/**
		 * Uses ConfigData to save physics information
		 */
		void Initialize() override;

		/**
		 * Allows other entities or systems to apply a force to this rigid body
		 */
		void ApplyForce(const math::Vector3& force);

		/**
		 * Force Accessor
		 */
		math::Vector3 GetForce() const;

		/**
		 * Removes all active forces from this component
		 */
		void ClearForce();

		/**
		 * Mass Accessors
		 */
		void SetMass(float mass);
		float GetMass() const;

		/**
		 * Inverse Mass Accessor
		 */
		float GetInverseMass() const;

		/**
		 * Velocity Accessor
		 */
		math::Vector3 GetVelocity() const;

		/**
		 * Velocity Accessor
		 */
		void AddVelocity(const math::Vector3& velocity);

		/**
		 * Restitution Accessor
		 */
		float GetRestitution() const;

		/**
		 * GravityScale Accessor
		 */
		float GetGravityScale() const;

		/**
		 * IsStatic Accessor
		 */
		bool GetIsStatic() const;

	private:
		/** The Entity's current velocity */
		math::Vector3 Velocity;

		/** Represents the sum of all the forces acting on the parent */
		math::Vector3 Force;

		/** The parent's mass */
		float Mass;

		/** The parent's inverse mass */
		float InverseMass;

		/** Scales how much gravity effects the parent */
		float GravityScale;

		/** Density of parent */
		float Density;

		/** Elasticity of parent */
		float Restitution;

		/** Enables or disables ability to move this object with physics */
		bool IsStatic;
	};

}

