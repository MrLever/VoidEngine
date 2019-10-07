#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "PlayerEntity.h"

namespace SuperVoid{

	/**
	 * @class PlayerShip
	 * @brief Represent's the player
	 */
	class PlayerShip : public core::PlayerEntity {
	public:
		/**
		 * Constructor
		 * @param name The player's name
		 */
		PlayerShip(const utils::Name& name);

		/**
		 * Constructor
		 * @param name The player's name
		 */
		PlayerShip(const std::string& name);

	};
}

