//STD Headers

//External Headers
#include <core/Scene.h>
#include <core/gameplay_framework/Entity.h>
#include <math/Vector.h>

//SuperVoid Headers

namespace SuperVoid {
	class Asteroid : public core::Entity {
		TYPE_INFO_DECL(Asteroid)

	public:
		/**
		 * Constructor
		 */
		Asteroid();

		/**
		 * Destructor
		 */
		~Asteroid() = default;

		/**
		 * Initialize member variables
		 */
		void Initialize() override;

		/**
		 * Rotates asteroid
		 */
		void Tick(float deltaSeconds) override;

		/**
		 * Causes asteroid to split
		 */
		void OnHit() override;

		/**
		 * Spawns two child asteroids
		 */
		void OnDestroy() override;

	private:
		float minScaleMagnitude;
	};
}