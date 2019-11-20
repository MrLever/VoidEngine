#include "SphereEntity.h"

namespace SuperVoid {
	ENABLE_FACTORY(SphereEntity, core::Entity)
	
	SphereEntity::SphereEntity() {
		Body.PhysicsEnabled = true;
	}
}