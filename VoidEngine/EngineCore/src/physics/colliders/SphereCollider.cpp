//STD Headers
#include <algorithm>

//Library Headers

//Void Engine Headers
#include "physics/colliders/SphereCollider.h"
#include "physics/colliders/AABBCollider.h"

namespace core {

	ENABLE_FACTORY(SphereCollider, Collider)

	SphereCollider::SphereCollider() : Radius(0.0f) {

	}

	void SphereCollider::Initialize() {
		Radius = configData["radius"].get<float>();
	}

	float SphereCollider::GetRadius() const {
		return Radius;
	}

	void SphereCollider::Draw(std::shared_ptr<ShaderProgram> shader, const glm::mat4& transform) {

	}

	utils::Name SphereCollider::GetTypename() const {
		return utils::Name("SphereCollider");
	}

	utils::Name SphereCollider::GetStaticTypename() {
		return utils::Name("SphereCollider");
	}

}