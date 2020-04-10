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

		void OnHit() override;

		void OnDestroy() override;

		
	private:

	};
}